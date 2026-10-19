pub struct Array {
    pub data: Vec<String>,
}

impl Array {
    pub fn new() -> Self {
        Array { data: Vec::new() }
    }

    pub fn push(&mut self, value: String) {
        self.data.push(value);
    }

    pub fn push_index(&mut self, index: usize, value: String) {
        if index <= self.data.len() {
            self.data.insert(index, value);
        }
    }

    pub fn get(&self, index: usize) -> Option<&String> {
        self.data.get(index)
    }

    pub fn set(&mut self, index: usize, value: String) {
        if index < self.data.len() {
            self.data[index] = value;
        }
    }

    pub fn del(&mut self, index: usize) {
        if index < self.data.len() {
            self.data.remove(index);
        }
    }

    pub fn len(&self) -> usize {
        self.data.len()
    }

    pub fn print(&self) {
        for item in &self.data {
            print!("{} ", item);
        }
        println!();
    }
}
