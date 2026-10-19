mod containers;
mod dbms;

use std::env;
use std::io::{self, BufRead};
use dbms::Database;

fn main() {
    let args: Vec<String> = env::args().collect();
    let mut file = String::new();
    let mut query = String::new();

    let mut i = 1;
    while i < args.len() {
        if args[i] == "--file" && i + 1 < args.len() {
            file = args[i + 1].clone();
            i += 2;
        } else if args[i] == "--query" && i + 1 < args.len() {
            query = args[i + 1].clone();
            i += 2;
        } else if args[i] == "-h" || args[i] == "--help" {
            println!("Usage: {} --file <path> --query '<cmd>'", args[0]);
            return;
        } else {
            eprintln!("Unknown argument: {}", args[i]);
            std::process::exit(2);
        }
    }

    if file.is_empty() {
        eprintln!("Need --file");
        std::process::exit(2);
    }

    let mut db = Database::new();
    db.load(&file);

    if !query.is_empty() {
        db.exec(&query);
        db.save(&file);
    } else {
        let stdin = io::stdin();
        for line in stdin.lock().lines() {
            if let Ok(l) = line {
                if !l.trim().is_empty() {
                    db.exec(&l);
                }
            }
        }
        db.save(&file);
    }
}
