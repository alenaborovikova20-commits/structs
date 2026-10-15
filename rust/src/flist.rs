use std::io::{self, Write};

type Link = Option<Box<Node>>;

pub struct Node {
    pub key: i32,
    pub next: Link,
}

pub struct Flist {
    pub head: Link,
}

impl Flist {
    pub fn new() -> Self {
        Flist { head: None }
    }

    pub fn clean(&mut self) {
        self.head = None;
    }

    pub fn push(&mut self, data: i32) {
        let new_node = Box::new(Node {
            key: data,
            next: self.head.take(),
        });
        self.head = Some(new_node);
    }

    pub fn push_end(&mut self, data: i32) {
        let mut cur = &mut self.head;
        while let Some(node) = cur {
            cur = &mut node.next;
        }
        *cur = Some(Box::new(Node { key: data, next: None }));
    }

    pub fn push_after(&mut self, target: i32, data: i32) -> bool {
        if let Some(node) = self.find_mut(target) {
            let new_node = Box::new(Node {
                key: data,
                next: node.next.take(),
            });
            node.next = Some(new_node);
            true
        } else {
            false
        }
    }

    pub fn push_before(&mut self, target: i32, data: i32) -> bool {
        if self.head.is_none() {
            return false;
        }
        if self.head.as_ref().unwrap().key == target {
            self.push(data);
            return true;
        }
        let mut cur = &mut self.head;
        while let Some(node) = cur {
            if let Some(next) = &node.next {
                if next.key == target {
                    let new_node = Box::new(Node {
                        key: data,
                        next: node.next.take(),
                    });
                    node.next = Some(new_node);
                    return true;
                }
            }
            cur = &mut node.next;
        }
        false
    }

    pub fn del_after(&mut self, target: i32) -> bool {
        if let Some(node) = self.find_mut(target) {
            if let Some(del) = node.next.take() {
                node.next = del.next;
                return true;
            }
        }
        false
    }

    pub fn del_head(&mut self) {
        if let Some(node) = self.head.take() {
            self.head = node.next;
        }
    }

    pub fn del_end(&mut self) {
        match self.head.take() {
            None => {}
            Some(mut node) => {
                if node.next.is_none() {
                    return;
                }
                self.head = Some(node);
                let mut cur = &mut self.head;
                while let Some(n) = cur {
                    if n.next.as_ref().map_or(false, |nn| nn.next.is_none()) {
                        n.next = None;
                        return;
                    }
                    cur = &mut n.next;
                }
            }
        }
    }

    pub fn del_before(&mut self, target: i32) -> bool {
        if self.head.is_none() {
            return false;
        }
        if self.head.as_ref().unwrap().key == target {
            return false;
        }
        if self.head.as_ref().unwrap().next.as_ref().map_or(false, |n| n.key == target) {
            self.del_head();
            return true;
        }
        let mut cur = &mut self.head;
        while let Some(node) = cur {
            if let Some(next) = &node.next {
                if next.next.as_ref().map_or(false, |nn| nn.key == target) {
                    let del = node.next.take().unwrap();
                    node.next = del.next;
                    return true;
                }
            }
            cur = &mut node.next;
        }
        false
    }

    pub fn find(&self, key: i32) -> Option<&Node> {
        let mut cur = &self.head;
        while let Some(node) = cur {
            if node.key == key {
                return Some(node);
            }
            cur = &node.next;
        }
        None
    }

    fn find_mut(&mut self, key: i32) -> Option<&mut Node> {
        let mut cur = &mut self.head;
        while let Some(node) = cur {
            if node.key == key {
                return Some(node);
            }
            cur = &mut node.next;
        }
        None
    }

    pub fn del(&mut self, key: i32) {
        if self.head.is_none() {
            return;
        }
        if self.head.as_ref().unwrap().key == key {
            self.del_head();
            return;
        }
        let mut cur = &mut self.head;
        while let Some(node) = cur {
            if node.next.as_ref().map_or(false, |n| n.key == key) {
                let del = node.next.take().unwrap();
                node.next = del.next;
                return;
            }
            cur = &mut node.next;
        }
    }

    pub fn print(&self) {
        let mut cur = &self.head;
        while let Some(node) = cur {
            print!("{} ", node.key);
            cur = &node.next;
        }
        println!();
    }

    pub fn save<W: Write>(&self, out: &mut W) -> io::Result<()> {
        let mut count = 0;
        let mut cur = &self.head;
        while let Some(node) = cur {
            count += 1;
            cur = &node.next;
        }
        writeln!(out, "{}", count)?;
        let mut cur = &self.head;
        while let Some(node) = cur {
            write!(out, "{} ", node.key)?;
            cur = &node.next;
        }
        writeln!(out)?;
        Ok(())
    }

    pub fn load(&mut self, input: &str) -> Result<(), String> {
        self.clean();
        let mut lines = input.lines();
        let count: usize = lines.next().ok_or("Нет данных")?
            .trim().parse().map_err(|_| "Ошибка размера")?;
        if count == 0 {
            return Ok(());
        }
        let data = lines.next().ok_or("Нет данных")?;
        for token in data.split_whitespace().take(count) {
            let v: i32 = token.parse().map_err(|_| "Ошибка числа")?;
            self.push_end(v);
        }
        Ok(())
    }
}