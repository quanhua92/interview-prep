pub struct TestCase {
    pub label: &'static str,
    pub input_arr: &'static [i32],
    pub target: i32,
    pub expected: &'static [i32],
}

pub fn print_arr(arr: &[i32]) {
    print!("[");
    for (i, v) in arr.iter().enumerate() {
        if i > 0 { print!(","); }
        print!("{}", v);
    }
    print!("]");
}

#[macro_export]
macro_rules! run_tests {
    ($name:expr, $solve_fn:ident, $tests:expr) => {{
        println!("\n============================================================");
        println!("  {}", $name);
        println!("============================================================");

        let mut passed = 0;
        let total = $tests.len();
        for (i, tc) in $tests.iter().enumerate() {
            let got = $solve_fn(tc.input_arr, tc.target);
            if got == tc.expected {
                passed += 1;
                println!("  Test {} ({}): PASS", i + 1, tc.label);
            } else {
                println!("  Test {} ({}): FAIL", i + 1, tc.label);
                println!("    Expected: {:?}", tc.expected);
                println!("    Got:      {:?}", got);
            }
        }

        println!("\n  {}/{} passed", passed, total);
        println!("============================================================\n");

        if passed == total { 0 } else { 1 }
    }};
}
