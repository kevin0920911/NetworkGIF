use std::net::{TcpListener, TcpStream};
use std::io::Write;

use rand::Rng;


const QUOTE:[&str; 10] = [
    "Always code as if the guy who ends up maintaining your code will be a violent psychopath who knows where you live. (Martin Golding)",
    "One man's crappy software is another man's full time job. (Jessica Gaston)",
    "If at first you don't succeed, call it version 1.0 (unknown)",
    "All programmers are playwrights and all computers are lousy actors. (Anonymous Hack Actor)",
    "Any code of your own that you haven't looked at for six or more months might as well have been written by someone else. (Eagleson's law)",
    "Commenting your code is like cleaning your bathroom — you never want to do it, but it really does create a more pleasant experience for you and your guests. (Ryan Campbell)",
    "In order to understand recursion, one must first understand recursion. (Anonymous)",
    "The best thing about a boolean is even if you are wrong, you are only off by a bit.",
    "Should array indices start at 0 or 1? My compromise of 0.5 was rejected without, I thought, proper consideration. (Stan Kelly-Bootle)",
    "Computers are good at following instructions, but not at reading your mind. (Donald Knuth)"
];


fn handle_client(mut stream: TcpStream) {
    let n = rand::thread_rng().gen_range(0..10);
    stream.write(&QUOTE[n].as_byte()).unwrap();
    println!("Server send: {}",QUOTE[n]);
}

fn main() {
    let listener = TcpListener::bind("127.0.0.1:1234").unwrap();
    println!("Waiting for connection!");
    for stream in listener.incoming() {

        match stream {
            Ok(stream) => {
                let client_addr = stream.peer_addr().unwrap();
                println!("New connection from {}", client_addr);
                handle_client(stream);
            }
            Err(_) => {
                println!("Error");
            }
        }

        
    }
}