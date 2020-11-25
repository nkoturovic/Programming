use nalgebra as na;

use na::{Matrix3, Vector3, Quaternion};

fn euler2a(fi : f64, teta : f64, psi : f64) -> Matrix3<f64> {
    let rx = Matrix3::<f64>::new(
        1.0, 0.0, 0.0,
        0.0, fi.cos(), -fi.sin(),
        0.0, fi.sin(), fi.cos()
    );

    let ry = Matrix3::<f64>::new(
        teta.cos(), 0.0, teta.sin(),
        0.0, 1.0, 0.0,
        -teta.sin(), 0.0, teta.cos()
    );

    let rz = Matrix3::<f64>::new(
        psi.cos(), -psi.sin(), 0.0,
        psi.sin(), psi.cos(), 0.0,
        0.0, 0.0, 1.0);

    rz * ry * rx
}


fn axis_angle(a : Matrix3<f64>) -> (Vector3<f64>, f64) {
    // P = A - E
    let pmat = a - Matrix3::<f64>::from_diagonal_element(1.0);

    let v = pmat.row(0).transpose().normalize();
    let u = pmat.row(1).transpose().normalize();
    let up = a * u; // u'
    let p = v.cross(&u).normalize();

    let fi = u.dot(&up).acos();

    if u.cross(&up).dot(&p) < 0.0 {
        (-p, fi)
    } else {
        (p, fi)
    }
}

fn rodrigez(p : Vector3<f64>, fi : f64) -> Matrix3<f64> {
    let pn = p.normalize();
    let px = Matrix3::<f64>::new(
        0.0, -pn.z, pn.y,
        pn.z, 0.0, -pn.x,
        -pn.y, pn.x, 0.0
    );

    // formula rodrigeza
    p*p.transpose() + fi.cos() *
        (Matrix3::<f64>::from_diagonal_element(1.0) -
            p*p.transpose()) + fi.sin() * px
}

fn a2euler(a : Matrix3<f64>) -> (f64, f64, f64) {
    if a[(2,0)] < 1.0 {
        if a[(2,0)] > -1.0 {
            return (
                a[(2,1)].atan2(a[(2,2)]) ,
                (-a[(2,0)]).asin(),
                a[(1,0)].atan2(a[(0,0)])
            );
        } else {
            return (
                0.0,
                std::f64::consts::PI/2.0,
                (-a[(0,1)]).atan2(a[(1,1)])
            );
        }
    } else {
        return (
            0.0,
            (-a[(0,1)]).atan2(a[(1,1)]),
            -std::f64::consts::PI/2.0
        );
    }
}

fn axis_angle2q(p : Vector3<f64>, fi : f64) -> Quaternion<f64> {
    let w = (fi/2.0).cos();
    let pn = p.normalize();
    let m = (fi/2.0).sin();
    Quaternion::<f64>::new(m * pn.x, m * pn.y, m * pn.z, w)
}

fn q2axis_angle(q : Quaternion<f64>) -> (Vector3<f64>, f64) {
    let mut q_norm = q.normalize();
    if q_norm.w < 0.0 {
        q_norm = -q_norm;
    }
    let fi = 2.0 * q_norm.w.acos();
    if q_norm.w.abs() == 1.0 {
        (Vector3::<f64>::new(1.0, 0.0, 0.0), fi)
    } else {
        (Vector3::<f64>::new(q_norm.i, q_norm.j, q_norm.k).normalize(), fi)
    }
}

fn prikazi_primer(fi : f64, teta : f64, psi : f64) {
    println!("------------------------------------------------------------");
    println!("Ojlerovi uglovi: (fi:{:.5}, teta:{:.5}, psi:{:.5})", fi, teta, psi);
    println!("------------------------------------------------------------");
    println!("Euler2A : Ojler -> Matrica A");
    let e2a_result = euler2a(fi, teta, psi);
    print!("  Matrica A = {:.5}", e2a_result);
    println!("------------------------------------------------------------");
    println!("AxisAngle : Matrica A -> (AroundVec, Ugao)");
    let (aa_v, aa_ang) = axis_angle(e2a_result);
    println!("  AroundVec = {:.5}  Ugao = {:.5}", aa_v, aa_ang);
    println!("------------------------------------------------------------");
    println!("Rodrigez : (AroundVec, Ugao) -> Matrica A");
    let rod_result = rodrigez(aa_v, aa_ang);
    print!(  "  Matrica A = {:.5}", rod_result);
    println!("------------------------------------------------------------");
    println!("A2Euler : Matrica A -> Ojler");
    let a2e_result = a2euler(rod_result);
    println!("  Ojler = (fi:{:.5}, teta:{:.5}, psi:{:.5})", 
                     a2e_result.0, a2e_result.1, a2e_result.2);
    println!("------------------------------------------------------------");
    println!("AxisAngle2Q : (AroundVec, Ugao) -> Kvaternion Q");
    let q = axis_angle2q(aa_v, aa_ang);
    print!(  "  Kvaternion Q = ");
    println!("{:.5} + {:.5}i + {:.5}j + {:.5}k", q.w, q.i, q.j, q.k);
    println!("------------------------------------------------------------");
    println!("Q2AxisAngle : Kvaternion Q -> (AroundVec, Ugao)");
    let (qaa_v, qaa_ang) = q2axis_angle(q);
    println!("  AroundVec = {:.5}  Ugao = {:.5}", qaa_v, qaa_ang);
    println!("------------------------------------------------------------");
}

fn main() {
    prikazi_primer(-f64::atan(1.0/4.0), -f64::asin(8.0/9.0), f64::atan(4.0));
}
