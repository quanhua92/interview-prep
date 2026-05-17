import urllib.request
import re
import json
import time
import sys
import html

def clean_html(raw_html):
    # Remove any internal HTML tags
    clean_text = re.sub(r'<[^>]+>', '', raw_html)
    # Unescape HTML entities (like &amp;, &#x27;)
    return html.unescape(clean_text).strip()

def scrape_calibre_section(section_slug):
    url = f"https://www.calibreos.com/learn?section={section_slug}"
    headers = {
        "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
    }
    
    print(f"Fetching section: {section_slug} ...")
    try:
        req = urllib.request.Request(url, headers=headers)
        with urllib.request.urlopen(req) as response:
            page_content = response.read().decode('utf-8')
    except Exception as e:
        print(f"  Error fetching {section_slug}: {e}")
        return []

    articles = []
    # Match the entire <a> block
    pattern = re.compile(r'<a[^>]+href="(/learn/[^"]+)"[^>]*>(.*?)</a>', re.DOTALL)
    
    for match in pattern.finditer(page_content):
        href = match.group(1)
        content = match.group(2)
        
        if 'section=' in href:
            continue
            
        article_url = f"https://www.calibreos.com{href}"
        article_id = href.split('/')[-1]
        
        # Title: inside <h2>
        title_match = re.search(r'<h2[^>]*>(.*?)</h2>', content, re.DOTALL)
        title = clean_html(title_match.group(1)) if title_match else "Unknown Title"
        
        # Snippet: inside <p>
        snippet_match = re.search(r'<p[^>]*>(.*?)</p>', content, re.DOTALL)
        snippet = clean_html(snippet_match.group(1)) if snippet_match else ""
        
        # Access
        is_pro = 'Pro content' in content or 'lucide-lock' in content or 'upgrade to unlock' in content.lower()
            
        # Duration
        duration_match = re.search(r'(\d+)\s*min', content)
        duration = f"{duration_match.group(1)} min" if duration_match else ""
        
        # Level
        level = ""
        for l in ['Advanced', 'Intermediate', 'Beginner']:
            if l in content:
                level = l
                break
                
        # Tags
        tag_matches = re.findall(r'<span[^>]+class="[^"]*rounded-sm[^"]*"[^>]*>(.*?)</span>', content)
        tags = [clean_html(t) for t in tag_matches if t.strip() and not t.strip().isdigit() and len(t.strip()) < 50]

        articles.append({
            "id": article_id,
            "section": section_slug,
            "title": title,
            "snippet": snippet,
            "url": article_url,
            "access": "paid" if is_pro else "free",
            "duration": duration,
            "level": level,
            "tags": tags
        })

    print(f"  Found {len(articles)} articles.")
    return articles

def main():
    sections = [
        "ml", "genai", "mlsd", "dsa", "hld", "lld", "prod", "craft", "data"
    ]
    
    all_articles = []
    seen_ids = set()
    
    for section in sections:
        section_data = scrape_calibre_section(section)
        for article in section_data:
            if article['id'] not in seen_ids:
                all_articles.append(article)
                seen_ids.add(article['id'])
        time.sleep(1)
    
    output_file = "all_calibre_articles.json"
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(all_articles, f, indent=2)
    
    print(f"\nTotal unique articles extracted: {len(all_articles)}")
    print(f"Data saved to {output_file}")

if __name__ == "__main__":
    main()
