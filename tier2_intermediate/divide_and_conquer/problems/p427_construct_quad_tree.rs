/*
 * P427: Construct Quad Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/construct-quad-tree/
 * Topics: Array, Divide and Conquer, Tree, Matrix
 * 
 * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
 * Return the root of the Quad-Tree representing grid.
 * A Quad-Tree is a tree data structure in which each internal node has exactly four children. Besides, each node has two attributes:
 * We can construct a Quad-Tree from a two-dimensional area using the following steps:
 * If you want to know more about the Quad-Tree, you can refer to the wiki.
 * Quad-Tree format:
 * You don't need to read this section for solving the problem. This is only if you want to understand the output format here. The output represents the serialized format of a Quad-Tree using level order traversal, where null signifies a path terminator where no node exists below.
 * It is very similar to the serialization of the binary tree. The only difference is that the node is represented as a list [isLeaf, val].
 * If the value of isLeaf or val is True we represent it as 1 in the list [isLeaf, val] and if the value of isLeaf or val is False we represent it as 0.
 *     class Node {
 *     public boolean val;
 *     public boolean isLeaf;
 *     public Node topLeft;
 *     public Node topRight;
 *     public Node bottomLeft;
 *     public Node bottomRight;
 *     }
 * 
 * Example 1:
 *     Input: grid = [[0,1],[1,0]]
 *     Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
 *     Explanation: The explanation of this example is shown below:
 *     Notice that 0 represents False and 1 represents True in the photo representing the Quad-Tree.
 * 
 * Example 2:
 *     Input: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
 *     Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
 *     Explanation: All values in the grid are not the same. We divide the grid into four sub-grids.
 *     The topLeft, bottomLeft and bottomRight each has the same value.
 *     The topRight have different values so we divide it into 4 sub-grids where each has the same value.
 *     Explanation is shown in the photo below:
 * 
 * Constraints:
 *     - n == grid.length == grid[i].length
 *     - n == 2x where 0 <= x <= 6
 * 
 * Template (python3):
 *     '''
 *     # Definition for a QuadTree node.
 *     class Node:
 *         def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
 *             self.val = val
 *             self.isLeaf = isLeaf
 *             self.topLeft = topLeft
 *             self.topRight = topRight
 *             self.bottomLeft = bottomLeft
 *             self.bottomRight = bottomRight
 *     '''
 * 
 *     class Solution:
 *         def construct(self, grid: List[List[int]]) -> 'Node':
 */
#[derive(Clone)]
struct QNode {
    is_leaf: bool,
    val: bool,
    tl: Option<Box<QNode>>,
    tr: Option<Box<QNode>>,
    bl: Option<Box<QNode>>,
    br: Option<Box<QNode>>,
}

fn all_same(grid: &[Vec<i32>], row: usize, col: usize, size: usize) -> bool {
    todo!()
}

fn build(grid: &[Vec<i32>], row: usize, col: usize, size: usize) -> Box<QNode> {
    todo!()
}

#[derive(Clone, Copy, PartialEq, Debug)]
enum FlatVal { Node(bool, bool), Null }

fn level_order(root: &QNode) -> Vec<FlatVal> {
    todo!()
}

fn print_flat(fv: &[FlatVal]) {
    todo!()
}

fn check(fv: &[FlatVal], expected: &[(bool, bool)]) -> bool {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  427. Construct Quad Tree");
    println!("============================================================");
    let mut passed = 0;
    let total = 5;

    {
        let grid = vec![vec![0,1],vec![1,0]];
        let root = build(&grid, 0, 0, 2);
        let got = level_order(&root);
        let exp = [(false,true),(true,false),(true,true),(true,true),(true,false)];
        if check(&got, &exp) { passed += 1; println!("  Test 1 (example 2): PASS"); }
        else { println!("  Test 1 (example 2): FAIL\n  Expected: [[0,1],[1,0],[1,1],[1,1],[1,0]]\n  Got:      "); print_flat(&got); println!(); }
    }
    {
        let grid = vec![
            vec![1,1,1,1,0,0,0,0],vec![1,1,1,1,0,0,0,0],vec![1,1,1,1,1,1,1,1],vec![1,1,1,1,1,1,1,1],
            vec![1,1,1,1,0,0,0,0],vec![1,1,1,1,0,0,0,0],vec![1,1,1,1,0,0,0,0],vec![1,1,1,1,0,0,0,0]
        ];
        let root = build(&grid, 0, 0, 8);
        let got = level_order(&root);
        let exp = [(false,true),(true,true),(false,true),(true,true),(true,false),(true,false),(true,false),(true,true),(true,true)];
        if check(&got, &exp) { passed += 1; println!("  Test 2 (example 3): PASS"); }
        else { println!("  Test 2 (example 3): FAIL\n  Expected: [[0,1],[1,1],[0,1],[1,1],[1,0],[1,0],[1,0],[1,1],[1,1]]\n  Got:      "); print_flat(&got); println!(); }
    }
    {
        let grid = vec![vec![0]];
        let root = build(&grid, 0, 0, 1);
        let got = level_order(&root);
        if check(&got, &[(true,false)]) { passed += 1; println!("  Test 3 (1x1 all zeros): PASS"); }
        else { println!("  Test 3 (1x1 all zeros): FAIL"); }
    }
    {
        let grid = vec![vec![1]];
        let root = build(&grid, 0, 0, 1);
        let got = level_order(&root);
        if check(&got, &[(true,true)]) { passed += 1; println!("  Test 4 (1x1 all ones): PASS"); }
        else { println!("  Test 4 (1x1 all ones): FAIL"); }
    }
    {
        let grid = vec![vec![1,1],vec![1,1]];
        let root = build(&grid, 0, 0, 2);
        let got = level_order(&root);
        if check(&got, &[(true,true)]) { passed += 1; println!("  Test 5 (2x2 all same ones): PASS"); }
        else { println!("  Test 5 (2x2 all same ones): FAIL"); }
    }

    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");
    std::process::exit(if passed == total { 0 } else { 1 });
}
