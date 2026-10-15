use std::io::{self, Write};

type Link = Option<Box<SNode>>;

pub struct SNode {
    pub field: i32,
    pub ptr: Link,
}

pub struct Stack {
    pub head: Link,
}

impl Stack {
    pub fn new() -> Self {
        Stack { head: None }
    }

    pub fn clean(&mut self) {
        self.head = None;
    }

    pub fn push(&mut self, data: i32) {
        let new_node = Box::new(SNode {
            field: data,
            ptr: self.head.take(),
        });
        self.head = Some(new_node);
    }

    pub fn pop(&mut self) {
        if let Some(node) = self.head.take() {
            self.head = node.ptr;
        }
    }

    pub fn print(&self) {
        let mut cur = &self.head;
        while let Some(node) = cur {
            println!("{}", node.field);
            cur = &node.ptr;
        }
    }

    pub fn save<W: Write>(&self, out: &mut W) -> io::Result<()> {
        let mut count = 0;
        let mut cur = &self.head;
        while let Some(node) = cur {
            count += 1;
            cur = &node.ptr;
        }
        writeln!(out, "{}", count)?;
        let mut cur = &self.head;
        while let Some(node) = cur {
            write!(out, "{} ", node.field)?;
            cur = &node.ptr;
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
        let vals: Vec<i32> = data.split_whitespace()
            .take(count)
            .filter_map(|t| t.parse().ok())
            .collect();
        for v in vals.into_iter().rev() {
            self.push(v);
        }
        Ok(())
    }
}