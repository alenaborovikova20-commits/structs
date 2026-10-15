mod array;
mod avl;
mod dlist;
mod flist;
mod queue;
mod stack;

use std::fs;
use std::io::{BufRead, BufReader, Write};

use array::Array;
use avl::AvlTree;
use dlist::Dlist;
use flist::Flist;
use queue::Queue;
use stack::Stack;

fn main() {
    let mut marr = Array::new();
    let mut flist = Flist::new();
    let mut dlist = Dlist::new();
    let mut queue = Queue::new();
    let mut stack = Stack::new();
    let mut tree = AvlTree::new();

    let file = fs::File::open("input.txt").expect("Cannot open input.txt");
    let reader = BufReader::new(file);

    for line in reader.lines() {
        let line = line.unwrap();
        if line.trim().is_empty() {
            continue;
        }
        let mut parts = line.split_whitespace();
        let cmd = match parts.next() {
            Some(c) => c,
            None => continue,
        };

        match cmd {
            "PRINT" => {
                let t = parts.next().unwrap_or("");
                match t {
                    "M" => marr.print(),
                    "F" => flist.print(),
                    "L" => dlist.print(),
                    "Q" => queue.print(),
                    "S" => stack.print(),
                    "T" => tree.print(),
                    _ => {}
                }
            }
            "MPUSH" => {
                let rest: Vec<i32> = parts.filter_map(|x| x.parse().ok()).collect();
                match rest.len() {
                    1 => marr.push(rest[0]),
                    2 => marr.push_index(rest[0] as usize, rest[1]),
                    _ => {}
                }
            }
            "MDEL" => {
                if let Some(i) = parts.next().and_then(|x| x.parse::<usize>().ok()) {
                    marr.del(i);
                }
            }
            "MGET" => {
                if let Some(i) = parts.next().and_then(|x| x.parse::<usize>().ok()) {
                    println!("{}", marr.get(i).unwrap_or(-1));
                }
            }
            "MSET" => {
                let vals: Vec<i32> = parts.filter_map(|x| x.parse().ok()).collect();
                if vals.len() == 2 {
                    marr.set(vals[0] as usize, vals[1]);
                }
            }
            "MLEN" => println!("{}", marr.len()),

            "FPUSH" => {
                if let Some(v) = parts.next().and_then(|x| x.parse().ok()) {
                    flist.push(v);
                }
            }
            "FDEL" => {
                if let Some(v) = parts.next().and_then(|x| x.parse().ok()) {
                    flist.del(v);
                }
            }
            "FGET" => {
                if let Some(v) = parts.next().and_then(|x| x.parse().ok()) {
                    let _ = flist.find(v);
                }
            }

            "LPUSH" => {
                if let Some(v) = parts.next().and_then(|x| x.parse().ok()) {
                    dlist.push(v);
                }
            }
            "LDEL" => {
                if let Some(v) = parts.next().and_then(|x| x.parse().ok()) {
                    dlist.del(v);
                }
            }
            "LGET" => {
                let _ = parts.next();
            }

            "QPUSH" => {
                if let Some(v) = parts.next().and_then(|x| x.parse().ok()) {
                    queue.push(v);
                }
            }
            "QPOP" => queue.pop(),

            "SPUSH" => {
                if let Some(v) = parts.next().and_then(|x| x.parse().ok()) {
                    stack.push(v);
                }
            }
            "SPOP" => stack.pop(),

            "TINSERT" => {
                if let Some(v) = parts.next().and_then(|x| x.parse().ok()) {
                    tree.insert_key(v);
                }
            }
            "TDEL" => {
                if let Some(v) = parts.next().and_then(|x| x.parse().ok()) {
                    tree.del(v);
                }
            }
            "TGET" => {
                if let Some(v) = parts.next().and_then(|x| x.parse().ok()) {
                    let _ = tree.get(v);
                }
            }
            _ => {}
        }
    }

    let mut out = fs::File::create("output.txt").expect("Cannot create output.txt");
    marr.save(&mut out).unwrap();
    flist.save(&mut out).unwrap();
    dlist.save(&mut out).unwrap();
    queue.save(&mut out).unwrap();
    stack.save(&mut out).unwrap();
    tree.save(&mut out).unwrap();
    out.flush().unwrap();
}