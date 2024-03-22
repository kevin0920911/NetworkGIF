use std::net::{TcpListener, TcpStream};
use std::thread;
use std::io::Read;
use std::io::Write;
use std::str;

fn handle_client(mut stream: TcpStream) {
    // read 20 bytes at a time from stream echoing back to stream
    loop {
        let mut read = [0; 1028];
        match stream.read(&mut read) {
            Ok(n) => {
                if n == 0  || read[0]==b'.'{ 
                    // connection was closed
                    println!("Waiting for connection!");
                    break;
                }
                println!("Server Recive: {}",str::from_utf8(&read).unwrap());
            }
            Err(err) => {
                panic!(err);
            }
        }
    }
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