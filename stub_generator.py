import re
from pathlib import Path

SKIP_FN_NAMES = {"main"}

def find_matching_brace(text, start):
    depth = 0
    in_str = None
    i = start
    while i < len(text):
        ch = text[i]
        if in_str:
            if ch == '\\': i += 2; continue
            if ch == in_str: in_str = None
        elif ch in ('"', "'"): in_str = ch
        elif ch == '/' and i + 1 < len(text):
            if text[i+1] == '/':
                while i < len(text) and text[i] != '\n': i += 1
                continue
            if text[i+1] == '*':
                end = text.find('*/', i+2)
                i = end + 2 if end >= 0 else len(text); continue
        elif ch == '{': depth += 1
        elif ch == '}':
            depth -= 1
            if depth == 0: return i
        i += 1
    return -1


def stub_text(content, lang):
    main_pat = '\nint main(' if lang in ('c', 'cpp') else '\nfn main('
    main_idx = -1
    idx = content.find(main_pat)
    if idx >= 0: main_idx = idx + 1

    if main_idx < 0:
        main_pat2 = '\nint main (' if lang in ('c', 'cpp') else '\nfn main ()'
        idx = content.find(main_pat2)
        if idx >= 0: main_idx = idx + 1

    if main_idx < 0:
        return content, False

    before_main = content[:main_idx]
    main_part = content[main_idx:]

    blocks = []
    i = 0
    in_block_comment = False
    while i < len(before_main):
        if in_block_comment:
            if i + 1 < len(before_main) and before_main[i] == '*' and before_main[i+1] == '/':
                in_block_comment = False; i += 2; continue
            i += 1; continue
        if before_main[i] == '/' and i+1 < len(before_main) and before_main[i+1] == '*':
            in_block_comment = True; i += 2; continue
        if before_main[i] == '/' and i+1 < len(before_main) and before_main[i+1] == '/':
            while i < len(before_main) and before_main[i] != '\n': i += 1
            continue
        if before_main[i] == '{':
            end = find_matching_brace(before_main, i)
            if end < 0: i += 1; continue
            pre = before_main[:i]
            brace_line_start = pre.rfind('\n') + 1
            brace_line = pre[brace_line_start:].strip()
            # If { is alone on its line, find the signature from previous lines
            sig_end = brace_line_start
            if not brace_line:
                # Walk backwards to find a line with (
                pos = brace_line_start - 1
                while pos >= 0:
                    nl = pre.rfind('\n', 0, pos)
                    sig_line = pre[nl+1:pos+1].strip() if nl >= 0 else pre[:pos+1].strip()
                    if '(' in sig_line:
                        sig_end = nl + 1 if nl >= 0 else 0
                        break
                    if not sig_line:
                        pos = nl - 1 if nl >= 0 else -1
                        continue
                    break
            last_line = pre[sig_end:].strip().split('\n')[-1].strip() if sig_end < len(pre) else ""
            full_sig = pre[sig_end:].rstrip()
            blocks.append((sig_end, i, end + 1, last_line, full_sig))
            i = end + 1
        else:
            i += 1

    if not blocks:
        return content, False

    any_stubbed = False
    result = []
    prev_end = 0

    for line_start, brace_start, brace_end, last_line, full_sig in blocks:
        result.append(before_main[prev_end:line_start])

        pre_text = before_main[:brace_start].strip()
        is_struct_enum = pre_text.endswith('}') or any(pre_text.rstrip().startswith(kw) for kw in ('struct', 'enum', 'union', 'typedef struct', 'typedef enum', 'typedef union'))

        m = re.search(r'(\w+)\s*\(', last_line)
        is_fn = m is not None and m.group(1) not in ('struct', 'enum', 'union', 'typedef', 'define', 'return', 'switch', 'case', 'if', 'while', 'for', 'else')

        if is_fn and not is_struct_enum:
            fname = m.group(1)
            if fname in SKIP_FN_NAMES:
                result.append(before_main[line_start:brace_end])
            else:
                any_stubbed = True
                sig_with_brace = before_main[line_start:brace_start+1]
                if lang in ('c', 'cpp'):
                    sig_with_brace = sig_with_brace.rstrip()
                    if not sig_with_brace.endswith('{'):
                        sig_with_brace += ' {'
                    result.append(sig_with_brace + '\n    abort();\n}')
                else:
                    sig_with_brace = sig_with_brace.rstrip()
                    if not sig_with_brace.endswith('{'):
                        sig_with_brace += ' {'
                    result.append(sig_with_brace + '\n    todo!()\n}')
        else:
            result.append(before_main[line_start:brace_end])

        prev_end = brace_end

    result.append(before_main[prev_end:])
    return ''.join(result) + main_part, any_stubbed


def extract_py_docstring(content):
    m = re.search(r'^"""(.*?)"""', content, re.DOTALL)
    if m: return m.group(1).strip()
    m = re.search(r"^'''(.*?)'''", content, re.DOTALL)
    return m.group(1).strip() if m else ""


def stub_js_text(content):
    lines = content.split("\n")
    result = []
    in_function = False
    brace_depth = 0
    fn_sig_lines = []
    any_stubbed = False

    i = 0
    while i < len(lines):
        line = lines[i]

        if not in_function:
            stripped = line.strip()
            if re.match(r'^(function\s+\w+|const\s+\w+\s*=\s*(async\s+)?function|class\s+\w+)', stripped):
                in_function = True
                fn_sig_lines = [line]
                brace_depth = line.count('{') - line.count('}')
                if brace_depth <= 0:
                    in_function = False
                i += 1
                continue

            result.append(line)
        else:
            fn_sig_lines.append(line)
            brace_depth += line.count('{') - line.count('}')
            if brace_depth <= 0:
                any_stubbed = True
                sig_text = fn_sig_lines[0].rstrip()
                if sig_text.endswith('{'):
                    sig_text = sig_text[:-1].rstrip()
                for sig_line in fn_sig_lines[1:-1]:
                    sig_text += "\n" + sig_line.rstrip().rstrip('{').rstrip()
                result.append(sig_text + " {")
                result.append('    throw new Error("NotImplementedError");')
                result.append("}")
                in_function = False
            i += 1
            continue

        i += 1

    return '\n'.join(result), any_stubbed


def main():
    tiers = sorted(Path(".").glob("tier*"))
    total = 0
    stubbed_files = 0

    for tier in tiers:
        if not tier.is_dir(): continue
        for cat_dir in sorted(tier.iterdir()):
            if not cat_dir.is_dir(): continue
            sol_dir = cat_dir / "solutions"
            prob_dir = cat_dir / "problems"
            if not sol_dir.exists() or not prob_dir.exists(): continue

            for py_file in sorted(sol_dir.glob("*.py")):
                if py_file.name == "__init__.py": continue
                stem = py_file.stem
                total += 1

                py_desc = ""
                try: py_desc = extract_py_docstring(py_file.read_text(errors="replace"))
                except: pass

                block_desc = ""
                if py_desc:
                    block_desc = "/*\n"
                    for line in py_desc.split("\n"): block_desc += f" * {line}\n"
                    block_desc += " */\n"

                js_desc = ""
                if py_desc:
                    js_desc = "/**\n"
                    for line in py_desc.split("\n"): js_desc += f" * {line}\n"
                    js_desc += " */\n"

                for ext, lang in [(".c", "c"), (".cpp", "cpp"), (".rs", "rs")]:
                    sol_file = sol_dir / f"{stem}{ext}"
                    prob_file = prob_dir / f"{stem}{ext}"
                    if not sol_file.exists(): continue

                    sol_content = sol_file.read_text(errors="replace")
                    old_desc_m = re.search(r'^/\*(.*?)\*/', sol_content, re.DOTALL)
                    after_desc = sol_content[old_desc_m.end():].lstrip("\n") if old_desc_m else sol_content

                    stubbed_content, was_stubbed = stub_text(after_desc, lang)
                    if not was_stubbed:
                        print(f"  WARNING: {stem}{ext} — no functions to stub, need manually edit")
                    else:
                        final = block_desc + stubbed_content
                        prob_file.write_text(final)
                        stubbed_files += 1

                sol_js = sol_dir / f"{stem}.mjs"
                prob_js = prob_dir / f"{stem}.mjs"
                if sol_js.exists():
                    sol_content = sol_js.read_text(errors="replace")
                    js_desc_m = re.search(r'^/\*\*(.*?)\*/', sol_content, re.DOTALL)
                    after_desc = sol_content[js_desc_m.end():].lstrip("\n") if js_desc_m else sol_content
                    stubbed_content, was_stubbed = stub_js_text(after_desc)
                    if not was_stubbed:
                        print(f"  WARNING: {stem}.mjs — no functions to stub, need manually edit")
                    else:
                        prob_js.write_text(js_desc + stubbed_content)
                        stubbed_files += 1

    print(f"Processed {total} problems, stubbed {stubbed_files} files")


if __name__ == "__main__":
    main()
