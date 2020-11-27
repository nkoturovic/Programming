use nalgebra as na;
use kiss3d as k3d;

/* Moguce je bilo koristiti ugradjene funkcije nalgebra biblioteke za * *
 * transformacije izmedju ojlerovih uglova, kvaterniona i sl. ali su    *
 * koriscene funkcije koje su prethodno implementirane u okviru domaceg */

fn main() {
    let mut window = k3d::window::Window::new("Slerp cube");
    let mut camera = k3d::camera::ArcBall::new(na::Point3::new(0.0, 0.0, 14.0), na::Point3::origin());
    window.set_light(k3d::light::Light::StickToCamera);

    // Parametri
    let mut animation_ongoing = false;
    let mut t = 0.0;
    let tmax = 1.0;
    let step = 0.005;

    // Pocetne pozicije, izmedju kojih se radi lerp
    let start_position = na::Vector3::new(-6.5, -3.0, 0.0);
    let end_position = na::Vector3::new(6.0, 3.0, 0.0);

    // Kada koristimo ojlerove uglove, ne smeju 2 biti 0 zbog gimbal lock-a
    let start_a = axis_angle(&euler2a(0.01, 0.01, 0.00));
    let end_a = axis_angle(&euler2a(
        std::f32::consts::PI/6.0, 
        std::f32::consts::PI, 
        -std::f32::consts::PI/4.0, 
     ));

    // Kvaternioni koji dobijeni funkcijama iz domaceg, koriste se za slerp
    let start_rot = na::UnitQuaternion::from_quaternion(axis_angle2q(&start_a.0, start_a.1));
    let end_rot = na::UnitQuaternion::from_quaternion(axis_angle2q(&end_a.0, end_a.1));

    // Kocka koju cemo da animiramo
    let mut cube = window.add_cube(1.0, 1.0, 1.0);
    cube.set_color(1.0, 0.0, 0.0);

    let mut start_cube = window.add_cube(1.0, 1.0, 1.0);
    start_cube.set_color(0.0, 1.0, 0.0);
    start_cube.set_points_size(10.0);
    start_cube.set_lines_width(2.0);
    start_cube.set_surface_rendering_activation(false);
    start_cube.set_local_transformation(na::Isometry::from_parts(na::Translation::from(start_position), start_rot));

    let mut end_cube = window.add_cube(1.0, 1.0, 1.0);
    end_cube.set_color(0.0, 1.0, 0.0);
    end_cube.set_points_size(10.0);
    end_cube.set_lines_width(2.0);
    end_cube.set_surface_rendering_activation(false);
    end_cube.set_local_transformation(na::Isometry::from_parts(na::Translation::from(end_position), end_rot));

    while window.render_with_camera(&mut camera) {
        for e in window.events().iter() {
            match e.value {
                kiss3d::event::WindowEvent::Key(key, _, _) => {
                    match key {
                        k3d::event::Key::G => animation_ongoing = true,
                        k3d::event::Key::S => animation_ongoing = false,
                        k3d::event::Key::R => { t = 0.0; animation_ongoing = false },
                        _ => {}
                    }
                },
                _ => {}
            }
        }

        draw_axis_at(&mut window, na::Isometry::from_parts(na::Translation::from(start_position), start_rot));
        draw_axis_at(&mut window, na::Isometry::from_parts(na::Translation::from(end_position), end_rot));

        let curr_transform = na::Isometry::from_parts(
            na::Translation::from(lerp(start_position, end_position, t, tmax)),
            slerp(start_rot, end_rot, tmax, t) //start_rot.slerp(&end_rot, t)
        );

        if animation_ongoing && t < tmax {
            t += step; 
        } else if t >= tmax {
            t = 1.0; 
            let restart_info = "Za restart pritisnite 'R'";
            window.draw_text(
                restart_info,
                &na::Point2::new((window.width() - 12*restart_info.len() as u32) as f32, window.height() as f32 - 70.0),
                60.0, &k3d::text::Font::default(), 
                &na::Point3::new(0.0, 1.0, 0.0)
            );
        } else if !animation_ongoing {
            let restart_info = "Za pokretanje pritisnite 'G'";
            window.draw_text(
                restart_info,
                &na::Point2::new((window.width() - 12*restart_info.len() as u32) as f32, window.height() as f32 - 70.0),
                60.0, &k3d::text::Font::default(), 
                &na::Point3::new(0.0, 1.0, 0.0)
            );

        }

        window.draw_text(
            &format!("Parametar t = {:.2}", t),
            &na::Point2::new(35.0, 2.0*window.height() as f32 - 70.0),
            60.0, &k3d::text::Font::default(), 
            &na::Point3::new(0.0, 1.0, 0.0)
        );

        cube.set_local_transformation(curr_transform);
        draw_axis_at(&mut window, curr_transform);
    }
}

fn slerp(q1 : na::UnitQuaternion<f32>,
         q2 : na::UnitQuaternion<f32>, 
         tm : f32, t : f32) -> na::UnitQuaternion<f32> {

    let mut cos0 = q1.dot(q2.quaternion());
    let mut q1_tmp : na::Quaternion<f32> = q1.quaternion().clone();

    if cos0 < 0.0 { 
        q1_tmp = -q1_tmp; 
        cos0 = -cos0;
    } 
    
    let fi0 = cos0.acos();

        if cos0 > 0.95 {
            na::UnitQuaternion::from_quaternion(q1_tmp)
        } else {
            na::UnitQuaternion::from_quaternion(
                ((fi0*(1.0-t/tm)).sin()/fi0.sin())*q1_tmp + ((fi0*t/tm).sin()/fi0.sin())*q2.quaternion()
            )
        }
}

fn draw_axis_at(window : &mut k3d::window::Window, location : na::Isometry3<f32> ) {
      let x1 = location * na::Point3::new(-1.0, 0.0, 0.0);
      let x2 = location * na::Point3::new(1.0, 0.0, 0.0);
      let y1 = location * na::Point3::new(0.0, -1.0, 0.0);
      let y2 = location * na::Point3::new(0.0, 1.0, 0.0);
      let z1 = location * na::Point3::new(0.0, 0.0, -1.0);
      let z2 = location * na::Point3::new(0.0, 0.0, 1.0);
      window.draw_line(&x1, &x2, &na::Point3::new(1.0, 0.0, 0.0));
      window.draw_line(&y1, &y2, &na::Point3::new(0.0, 1.0, 0.0));
      window.draw_line(&z1, &z2, &na::Point3::new(0.0, 0.0, 1.0));
}

fn euler2a(fi : f32, teta : f32, psi : f32) -> na::Matrix3<f32> {
    let rx = na::Matrix3::<f32>::new(
        1.0, 0.0, 0.0,
        0.0, fi.cos(), -fi.sin(),
        0.0, fi.sin(), fi.cos()
    );

    let ry = na::Matrix3::<f32>::new(
        teta.cos(), 0.0, teta.sin(),
        0.0, 1.0, 0.0,
        -teta.sin(), 0.0, teta.cos()
    );

    let rz = na::Matrix3::<f32>::new(
        psi.cos(), -psi.sin(), 0.0,
        psi.sin(), psi.cos(), 0.0,
        0.0, 0.0, 1.0);

    rz * ry * rx
}

fn axis_angle(a : &na::Matrix3<f32>) -> (na::Vector3<f32>, f32) {
    // P = A - E
    let pmat = a - na::Matrix3::<f32>::from_diagonal_element(1.0);

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

#[allow(dead_code)]
fn rodrigez(p : &na::Vector3<f32>, fi : f32) -> na::Matrix3<f32> {
    let pn = p.normalize();
    let px = na::Matrix3::<f32>::new(
        0.0, -pn.z, pn.y,
        pn.z, 0.0, -pn.x,
        -pn.y, pn.x, 0.0
    );

    // formula rodrigeza
    p*p.transpose() + fi.cos() *
        (na::Matrix3::<f32>::from_diagonal_element(1.0) -
            p*p.transpose()) + fi.sin() * px
}

#[allow(dead_code)]
fn a2euler(a : &na::Matrix3<f32>) -> (f32, f32, f32) {
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
                std::f32::consts::PI/2.0,
                (-a[(0,1)]).atan2(a[(1,1)])
            );
        }
    } else {
        return (
            0.0,
            (-a[(0,1)]).atan2(a[(1,1)]),
            -std::f32::consts::PI/2.0
        );
    }
}

fn axis_angle2q(p : &na::Vector3<f32>, fi : f32) -> na::Quaternion<f32> {
    let w = (fi/2.0).cos();
    let pn = p.normalize();
    let m = (fi/2.0).sin();
    na::Quaternion::<f32>::new(w, m*pn.x, m*pn.y, m*pn.z)
}

#[allow(dead_code)]
fn q2axis_angle(q : &na::Quaternion<f32>) -> (na::Vector3<f32>, f32) {
    let q_norm = 
        if q.w >= 0.0 { q.normalize() }
        else { -q.normalize() };
    let fi = 2.0 * q_norm.w.acos();
    if q_norm.w.abs() == 1.0 {
        (na::Vector3::<f32>::new(1.0, 0.0, 0.0), fi)
    } else {
        (na::Vector3::<f32>::new(q_norm.i, q_norm.j, q_norm.k).normalize(), fi)
    }
}

fn lerp(start : na::Vector3<f32>, end : na::Vector3<f32>, t : f32, tmax : f32) -> na::Vector3<f32> {
    na::Vector3::new(
        (1.0 - t/tmax) * start.x + t/tmax * end.x,
        (1.0 - t/tmax) * start.y + t/tmax * end.y,
        (1.0 - t/tmax) * start.z + t/tmax * end.z,
    )
}
