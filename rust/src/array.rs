use std::io::{self, Read, Write};

#[derive(Default)]
pub struct Array {
    data: Vec<i32>,
}

impl Array {
    pub fn new() -> Self {
        Array { data: Vec::new() }
    }

    pub fn push(&mut self, value: i32) {
        self.data.push(value);
    }

    pub fn push_index(&mut self, index: usize, value: i32) {
        if index <= self.data.len() {
            self.data.insert(index, value);
        }
    }

    pub fn get(&self, index: usize) -> Option<i32> {
        self.data.get(index).copied()
    }

    pub fn del(&mut self, index: usize) {
        if index < self.data.len() {
            self.data.remove(index);
        }
    }

    pub fn set(&mut self, index: usize, value: i32) {
        if let Some(slot) = self.data.get_mut(index) {
            *slot = value;
        }
    }

    pub fn len(&self) -> usize {
        self.data.len()
    }

    pub fn is_empty(&self) -> bool {
        self.data.is_empty()
    }

    pub fn print(&self) {
        if self.data.is_empty() {
            println!("Array is empty");
            return;
        }
        for v in &self.data {
            print!("{} ", v);
        }
        println!();
    }

    pub fn save<W: Write>(&self, out: &mut W) -> io::Result<()> {
        writeln!(out, "{}", self.data.len())?;
        for v in &self.data {
            write!(out, "{} ", v)?;
        }
        writeln!(out)?;
        Ok(())
    }

    pub fn load<R: Read>(&mut self, input: &str) -> Result<(), String> {
        let mut lines = input.lines();
        let count_line = lines.next().ok_or("Нет данных")?;
        let count: usize = count_line.trim().parse().map_err(|_| "Ошибка размера")?;
        self.data.clear();
        if count == 0 {
            return Ok(());
        }
        let data_line = lines.next().ok_or("Нет данных")?;
        for token in data_line.split_whitespace().take(count) {
            let v: i32 = token.parse().map_err(|_| "Ошибка числа")?;
            self.data.push(v);
        }
        Ok(())
    }
}