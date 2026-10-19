use std::collections::VecDeque;

pub struct Queue {
    pub data: VecDeque<String>,
}

impl Queue {
    pub fn new() -> Self {
        Queue { data: VecDeque::new() }
    }

    pub fn push(&mut self, value: String) {
        self.data.push_back(value);
    }

    pub fn pop(&mut self) -> Option<String> {
        self.data.pop_front()
    }

    pub fn print(&self) {
        for item in &self.data {
            print!("{} ", item);
        }
        println!();
    }
}
