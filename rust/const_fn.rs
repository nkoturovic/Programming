use std::io::{ stdin };

const fn plus3(x : i32) -> i32 {
    x + 3
}
const FIVE : i32 = plus3(2);

fn main() {
    let mut buf = String::new();
    let size = stdin().read_line(&mut buf).unwrap();
    let num : i32 = buf[0..size-1].parse().unwrap();
    println!("{}", plus3(num));
}
