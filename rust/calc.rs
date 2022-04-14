fn reversed_polish(expr:&str )-> f32{
  let mut stack: Vec<f32> = Vec::new();
  let split = expr.split_whitespace();
  for arg in split {
    let is_num = arg.parse::<f32>().is_ok();
    if is_num{
      stack.push(arg.parse::<f32>().unwrap());
    }else{
        let left:f32= stack.pop().unwrap();
        let right:f32= stack.pop().unwrap();
        if arg=="+"{
          stack.push(left + right);
        }
        if arg=="-"{
          stack.push(left - right);
        }
        if arg=="*"{
          stack.push(left * right);
        }
        if arg=="/"{
          stack.push(left / right);
        }        
    }
  }
  stack.pop().unwrap()
}

fn main() {
    let hello = String::from("3 6.5 + 8 -");
    println!("{}",reversed_polish(&hello));
}