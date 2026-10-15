use std::io::{self, Write};

type Link = Option<Box<QNode>>;

pub struct QNode {
    pub data: i32,
    pub next: Link,
}

pub struct Queue {
    pub head: Link,
    pub tail: *mut QNode,
}

impl Queue {
    pub fn new() -> Self {
        Queue {
            head: None,
            tail: std::ptr::null_mut(),
        }
    }

    pub fn clean(&mut self) {
        self.head = None;
        self.tail = std::ptr::null_mut();
    }

    pub fn push(&mut self, data: i32) {
        let mut new_node = Box::new(QNode { data, next: None });
        let raw: *mut QNode = &mut *new_node;
        if self.tail.is_null() {
            self.head = Some(new_node);
        } else {
            unsafe {
                (*self.tail).next = Some(new_node);
            }
        }
        self.tail = raw;
    }

    pub fn pop(&mut self) {
        if let Some(mut node) = self.head.take() {
            self.head = node.next.take();
            if self.head.is_none() {
                self.tail = std::ptr::null_mut();
            }
        }
    }

    pub fn print(&self) {
        let mut cur = &self.head;
        while let Some(node) = cur {
            print!("{} ", node.data);
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
            write!(out, "{} ", node.data)?;
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
            self.push(v);
        }
        Ok(())
    }
}