use nalgebra as na;

type Vec3 = na::Vector3<f64>;
type M2x9 = na::MatrixMN<f64,na::U2,na::U9>;
type M3x3 = na::Matrix3<f64>;

fn napravi_matricu_sistema(x : &Vec3, xp : &Vec3) -> M2x9 {
    M2x9::from_row_slice(
        &[0.0, 0.0, 0.0, -xp.z*x.x, -xp.z*x.y, -xp.z*x.z, xp.y*x.x, xp.y*x.y, xp.y*x.z,
          xp.z*x.x, xp.z*x.y, xp.z*x.z, 0.0, 0.0, 0.0, -xp.x*x.x, -xp.x*x.y, -xp.x*x.z]
    )
}

fn napravi_matricu_p(x1 : &Vec3, x2 : &Vec3, x3 : &Vec3, x4 : &Vec3) -> M3x3 {
    let x = M3x3::new(
        x1.x, x2.x, x3.x,
        x1.y, x2.y, x3.y,
        x1.z, x2.z, x3.z
    );

    let dekomp = x.lu();
    let resenje = dekomp.solve(&x4).expect("Solving equation failed");

    M3x3::new(
        resenje.x * x1.x, resenje.x * x1.y, resenje.x * x1.z,
        resenje.y * x2.x, resenje.y * x2.y, resenje.y * x2.z,
        resenje.z * x3.x, resenje.z * x3.y, resenje.z * x3.z,
    ).transpose()
}

fn naivni(x1 : &Vec3, x2 : &Vec3, x3 : &Vec3, x4: &Vec3, 
                    x1p : &Vec3, x2p : &Vec3, x3p : &Vec3, x4p : &Vec3) -> M3x3 {
    let mut p1 = napravi_matricu_p(&x1,&x2,&x3,&x4);
    let p2 = napravi_matricu_p(&x1p,&x2p,&x3p,&x4p);
    p1.try_inverse_mut();
    p2 * p1
}

fn dlt(tacke : &Vec<(Vec3, Vec3)>) -> M3x3 {
    let mut ms : Vec<M2x9> = vec![];
    for (x, xp) in tacke.iter() {
        ms.push(napravi_matricu_sistema(&x, &xp));
    }

    let r : Vec<_> = ms.iter().map(|x| x.as_slice()).collect();
    let m = na::DMatrix::from_row_slice(
        tacke.len() * 2,
        9,
        &r.as_slice().concat()
    );

    let svd = na::SVD::new(m, false, true);
    let vt = svd.v_t.expect("SVD algoritam nije moguce primeniti na matricu m");
    M3x3::from_row_slice(vt.column(vt.ncols() - 1).as_slice())
}


fn main() {
	let a = Vec3::new(-3.0, -1.0, 1.0);
	let b = Vec3::new(3.0, -1.0, 1.0);
	let c = Vec3::new(1.0, 1.0, 1.0);
	let d = Vec3::new(-1.0, 1.0, 1.0);
    let e = Vec3::new(1.0, 2.0, 3.0);
    let f = Vec3::new(-8.0, -2.0, 1.0);

	let ap = Vec3::new(-2.0, -1.0, 1.0);
	let bp = Vec3::new(2.0, -1.0, 1.0);
	let cp = Vec3::new(2.0, 1.0, 1.0);
	let dp = Vec3::new(-2.0, 1.0, 1.0);
    let ep = Vec3::new(2.0, 1.0 , 4.0);
    let fp = Vec3::new(-16.0, -5.0, 4.0);

    let nrez = naivni(&a, &b, &c, &d, &ap, &bp, &cp, &dp);
    println!("Naivnim algoritmom dobijamo: ");
    println!("{:.2}", &nrez);

    let drez = dlt(&vec![(a, ap), (b, bp), (c, cp), (d, dp), (e, ep), (f, fp)]);
    println!("DLT algoritmom dobijamo: ");
    println!("{:.2}", drez);
}
