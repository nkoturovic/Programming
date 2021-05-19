// Type your code here, or load an example.
fn main() {
    let ls: Vec<i32> = vec![1,2,3,4];
    let result = 
        ls.into_iter().filter(|&x| x%2 == 0).collect::<Vec<i32>>();

    for x in result {
        println!("{}", x);
    }
}
