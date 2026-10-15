use std::io::{self, Write};

type Link = Option<Box<DNode>>;

pub struct DNode {
    pub key: i32,
    pub prev: *mut DNode,
    pub next: Link,
}

pub struct Dlist {
    pub head: Link,
}

impl Dlist {
    pub fn new() -> Self {
        Dlist { head: None }
    }

    pub fn clean(&mut self) {
        self.head = None;
    }

    pub fn push(&mut self, data: i32) {
        let mut new_node = Box::new(DNode {
            key: data,
            prev: std::ptr::null_mut(),
            next: self.head.take(),
        });


        let raw: *mut DNode = &mut *new_node;

        if let Some(old_head) = new_node.next.as_mut() {
            old_head.prev = raw;
        }

        self.head = Some(new_node);
    }

    pub fn push_end(&mut self, data: i32) {
        let mut new_node = Box::new(DNode {
            key: data,
            prev: std::ptr::null_mut(),
            next: None,
        });

        if self.head.is_none() {
            self.head = Some(new_node);
            return;
        }


        let mut cur: *mut DNode = match self.head.as_mut() {
            Some(b) => &mut **b as *mut DNode,
            None => return,
        };

        unsafe {
            while (*cur).next.is_some() {
                cur = &mut **(*cur).next.as_mut().unwrap() as *mut DNode;
            }
            new_node.prev = cur;
            (*cur).next = Some(new_node);
        }
    }

    pub fn del_head(&mut self) {
        if let Some(mut node) = self.head.take() {
            if let Some(next) = node.next.as_mut() {
                next.prev = std::ptr::null_mut();
            }
            self.head = node.next.take();
        }
    }

    pub fn del_end(&mut self) {
        if self.head.is_none() {
            return;
        }
        if self.head.as_ref().unwrap().next.is_none() {
            self.head = None;
            return;
        }
        let mut cur: *mut DNode = &mut **self.head.as_mut().unwrap() as *mut DNode;
        unsafe {
            while (*cur).next.as_ref().map_or(false, |n| n.next.is_some()) {
                cur = &mut **(*cur).next.as_mut().unwrap() as *mut DNode;
            }
            (*cur).next = None;
        }
    }

    pub fn del(&mut self, key: i32) {
    if self.head.is_none() {
        return;
    }
    if self.head.as_ref().unwrap().key == key {
        self.del_head();
        return;
    }

    let mut cur: *mut DNode = &mut **self.head.as_mut().unwrap() as *mut DNode;

    unsafe {
        while (*cur).next.is_some() {
            let next_ptr: *mut DNode = &mut **(*cur).next.as_mut().unwrap() as *mut DNode;
            if (*next_ptr).key == key {
                let del = (*cur).next.take().unwrap();
                if let Some(nn) = del.next.as_ref() {
                    let nn_ptr = &**nn as *const DNode as *mut DNode;
                    (*nn_ptr).prev = cur;
                }
                (*cur).next = del.next;
                return;
            }
            cur = next_ptr;
        }
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

    pub fn print_reverse(&self) {
        fn rec(node: &Link) {
            if let Some(n) = node {
                rec(&n.next);
                print!("{} ", n.key);
            }
        }
        rec(&self.head);
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