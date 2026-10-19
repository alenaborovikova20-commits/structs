use std::collections::HashMap;
use std::fs::File;
use std::io::{BufRead, BufReader, Write};
use crate::containers::array::Array;
use crate::containers::flist::Flist;
use crate::containers::dlist::Dlist;
use crate::containers::queue::Queue;
use crate::containers::stack::Stack;

pub enum Entry {
    Arr(Array),
    Fl(Flist),
    Dl(Dlist),
    Qu(Queue),
    St(Stack),
}

pub struct Database {
    pub db: HashMap<String, Entry>,
}

impl Database {
    pub fn new() -> Self {
        Database { db: HashMap::new() }
    }

    pub fn exec(&mut self, query: &str) {
        let mut parts = query.split_whitespace();
        let cmd = match parts.next() {
            Some(c) => c,
            None => return,
        };
        let name = match parts.next() {
            Some(n) => n,
            None => {
                println!("ERR: missing name");
                return;
            }
        };

        if cmd == "MPUSH" {
            let v = parts.next().unwrap_or("").to_string();
            self.get_or_create_array(name).push(v);
        } else if cmd == "MPUSH_INDEX" {
            let i = parts.next().unwrap_or("0").parse().unwrap_or(0);
            let v = parts.next().unwrap_or("").to_string();
            self.get_or_create_array(name).push_index(i, v);
        } else if cmd == "MGET" {
            let i = parts.next().unwrap_or("0").parse().unwrap_or(0);
            if let Some(Entry::Arr(arr)) = self.db.get(name) {
                if let Some(val) = arr.get(i) { println!("{}", val); }
            }
        } else if cmd == "MSET" {
            let i = parts.next().unwrap_or("0").parse().unwrap_or(0);
            let v = parts.next().unwrap_or("").to_string();
            self.get_or_create_array(name).set(i, v);
        } else if cmd == "MDEL" {
            let i = parts.next().unwrap_or("0").parse().unwrap_or(0);
            self.get_or_create_array(name).del(i);
        } else if cmd == "MLEN" {
            if let Some(Entry::Arr(arr)) = self.db.get(name) {
                println!("{}", arr.len());
            }
        } else if cmd == "MPRINT" {
            if let Some(Entry::Arr(arr)) = self.db.get(name) { arr.print(); }
        
        } else if cmd == "FPUSH" {
            let v = parts.next().unwrap_or("").to_string();
            self.get_or_create_flist(name).push(v);
        } else if cmd == "FDEL" {
            let v = parts.next().unwrap_or("");
            self.get_or_create_flist(name).del(v);
        } else if cmd == "FGET" {
            let v = parts.next().unwrap_or("");
            if let Some(Entry::Fl(f)) = self.db.get(name) {
                println!("{}", if f.contains(v) { "TRUE" } else { "FALSE" });
            }
        } else if cmd == "FPRINT" {
            if let Some(Entry::Fl(f)) = self.db.get(name) { f.print(); }

        } else if cmd == "LPUSH" {
            let v = parts.next().unwrap_or("").to_string();
            self.get_or_create_dlist(name).push(v);
        } else if cmd == "LDEL" {
            let v = parts.next().unwrap_or("");
            self.get_or_create_dlist(name).del(v);
        } else if cmd == "LGET" {
            let v = parts.next().unwrap_or("");
            if let Some(Entry::Dl(d)) = self.db.get(name) {
                println!("{}", if d.contains(v) { "TRUE" } else { "FALSE" });
            }
        } else if cmd == "LPRINT" {
            if let Some(Entry::Dl(d)) = self.db.get(name) { d.print(); }

        } else if cmd == "QPUSH" {
            let v = parts.next().unwrap_or("").to_string();
            self.get_or_create_queue(name).push(v);
        } else if cmd == "QPOP" {
            if let Some(Entry::Qu(q)) = self.db.get_mut(name) {
                if let Some(val) = q.pop() { println!("{}", val); }
            }
        } else if cmd == "QPRINT" {
            if let Some(Entry::Qu(q)) = self.db.get(name) { q.print(); }

        } else if cmd == "SPUSH" {
            let v = parts.next().unwrap_or("").to_string();
            self.get_or_create_stack(name).push(v.clone());
            println!("{}", v);
        } else if cmd == "SPOP" {
            if let Some(Entry::St(s)) = self.db.get_mut(name) {
                if let Some(val) = s.pop() { println!("{}", val); }
            }
        } else if cmd == "SPRINT" {
            if let Some(Entry::St(s)) = self.db.get(name) { s.print(); }

        } else {
            println!("ERR: unknown command '{}'", cmd);
        }
    }

    fn get_or_create_array(&mut self, name: &str) -> &mut Array {
        self.db.entry(name.to_string()).or_insert_with(|| Entry::Arr(Array::new()));
        if let Entry::Arr(arr) = self.db.get_mut(name).unwrap() { arr } else { panic!("Type mismatch") }
    }
    fn get_or_create_flist(&mut self, name: &str) -> &mut Flist {
        self.db.entry(name.to_string()).or_insert_with(|| Entry::Fl(Flist::new()));
        if let Entry::Fl(f) = self.db.get_mut(name).unwrap() { f } else { panic!("Type mismatch") }
    }
    fn get_or_create_dlist(&mut self, name: &str) -> &mut Dlist {
        self.db.entry(name.to_string()).or_insert_with(|| Entry::Dl(Dlist::new()));
        if let Entry::Dl(d) = self.db.get_mut(name).unwrap() { d } else { panic!("Type mismatch") }
    }
    fn get_or_create_queue(&mut self, name: &str) -> &mut Queue {
        self.db.entry(name.to_string()).or_insert_with(|| Entry::Qu(Queue::new()));
        if let Entry::Qu(q) = self.db.get_mut(name).unwrap() { q } else { panic!("Type mismatch") }
    }
    fn get_or_create_stack(&mut self, name: &str) -> &mut Stack {
        self.db.entry(name.to_string()).or_insert_with(|| Entry::St(Stack::new()));
        if let Entry::St(s) = self.db.get_mut(name).unwrap() { s } else { panic!("Type mismatch") }
    }

    pub fn load(&mut self, path: &str) -> bool {
        let file = match File::open(path) { Ok(f) => f, Err(_) => return false };
        let reader = BufReader::new(file);
        self.db.clear();

        for line in reader.lines() {
            let line = line.unwrap_or_default();
            if line.is_empty() { continue; }
            let mut parts = line.split_whitespace();
            let type_char = parts.next().unwrap_or("");
            let name = parts.next().unwrap_or("").to_string();
            let n_str = parts.next().unwrap_or("0");
            let n: usize = n_str.parse().unwrap_or(0);

            match type_char {
                "A" => {
                    let mut arr = Array::new();
                    for _ in 0..n {
                        if let Some(v) = parts.next() { arr.push(v.to_string()); }
                    }
                    self.db.insert(name, Entry::Arr(arr));
                }
                "F" => {
                    let mut vals = Vec::new();
                    for _ in 0..n { if let Some(v) = parts.next() { vals.push(v.to_string()); } }
                    let mut f = Flist::new();
                    for v in vals.into_iter().rev() { f.push(v); }
                    self.db.insert(name, Entry::Fl(f));
                }
                "L" => {
                    let mut vals = Vec::new();
                    for _ in 0..n { if let Some(v) = parts.next() { vals.push(v.to_string()); } }
                    let mut d = Dlist::new();
                    for v in vals.into_iter().rev() { d.push(v); }
                    self.db.insert(name, Entry::Dl(d));
                }
                "Q" => {
                    let mut q = Queue::new();
                    for _ in 0..n { if let Some(v) = parts.next() { q.push(v.to_string()); } }
                    self.db.insert(name, Entry::Qu(q));
                }
                "S" => {
                    let mut vals = Vec::new();
                    for _ in 0..n { if let Some(v) = parts.next() { vals.push(v.to_string()); } }
                    let mut s = Stack::new();
                    for v in vals { s.push(v); }
                    self.db.insert(name, Entry::St(s));
                }
                _ => {}
            }
        }
        true
    }

    pub fn save(&self, path: &str) -> bool {
        let mut file = match File::create(path) { Ok(f) => f, Err(_) => return false };

        for (name, entry) in &self.db {
            match entry {
                Entry::Arr(arr) => {
                    let _ = write!(file, "A {} {}", name, arr.data.len());
                    for v in &arr.data { let _ = write!(file, " {}", v); }
                    let _ = writeln!(file);
                }
                Entry::Fl(f) => {
                    let mut items = Vec::new();
                    let mut curr = &f.head;
                    while let Some(node) = curr {
                        items.push(&node.key);
                        curr = &node.next;
                    }
                    let _ = write!(file, "F {} {}", name, items.len());
                    for v in items { let _ = write!(file, " {}", v); }
                    let _ = writeln!(file);
                }
                Entry::Dl(d) => {
                    let mut items = Vec::new();
                    let mut curr = d.head.clone();
                    while let Some(node) = curr {
                        items.push(node.borrow().key.clone());
                        let next = node.borrow().next.clone();
                        curr = next;
                    }
                    let _ = write!(file, "L {} {}", name, items.len());
                    for v in items { let _ = write!(file, " {}", v); }
                    let _ = writeln!(file);
                }
                Entry::Qu(q) => {
                    let _ = write!(file, "Q {} {}", name, q.data.len());
                    for v in &q.data { let _ = write!(file, " {}", v); }
                    let _ = writeln!(file);
                }
                Entry::St(s) => {
                    let _ = write!(file, "S {} {}", name, s.data.len());
                    for v in &s.data { let _ = write!(file, " {}", v); }
                    let _ = writeln!(file);
                }
            }
        }
        true
    }
}
