#[derive(Debug)]
struct Person {
    age : u8,
    name : &'static str,
    weight : f32,
    arena : Option<&'static str>
}

enum WeightCategory {LightWeight, MidWeight, HeavyWeight}

impl Person {
    fn is_adult(&self) -> bool { self.age >= 18 }
    fn weight_category(&self) -> WeightCategory {
        if self.weight < 70.0 {
            WeightCategory::LightWeight
        } else if 70.0 <= self.weight && self.weight < 80.0 {
            WeightCategory::MidWeight
        } else {
            WeightCategory::HeavyWeight
        }
    }
}

impl Person {
    fn arena_name(&self) -> Result<&'static str,&'static str> {
        match &self.arena {
            Some(arena) => Ok(arena),
            None => Err("Player does not have arena")
        }
    }
}

fn join(xs : &[String]) -> String {
    xs.join(",")
}

fn main() {
    std::env::args_os().for_each(|arg| println!("{:?}",arg));

    let p = Person { 
        age: 32, 
        name: "Mike",
        weight: 72.0,
        arena: Some("Plaza")
    };
    println!("{:?}", p);
    println!("{:?}", p.arena_name());
}
