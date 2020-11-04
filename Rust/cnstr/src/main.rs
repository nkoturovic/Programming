#![feature(min_const_generics)]

trait Cnstr<T> {
    fn is_satisfied(value : &T) -> bool;
    fn name() -> &'static str;
}

struct Length<const FROM : usize, const TO : usize>;
// impl<const FROM : usize, const TO : usize> Length<FROM, TO> {
//     fn from() -> usize { FROM }
//     fn to() -> usize { TO }
// }

impl<const FROM : usize, const TO : usize> Cnstr<&str> for Length<FROM, TO> {
    fn is_satisfied(value : &&str) -> bool { FROM <= value.len() && value.len() <= TO }
    fn name() -> &'static str { 
       "Length<{}, {}>"
    }
}

fn main() {
    type Length15 = Length::<1,5>;
    println!("{}", Length15::is_satisfied(&"Hello"));
    println!("{}", Length15::name());
}
