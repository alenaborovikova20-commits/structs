pub struct Stack {
    pub data: Vec<String>,
}

impl Stack {
    pub fn new() -> Self {
        Stack { data: Vec::new() }
    }

    pub fn push(&mut self, value: String) {
        self.data.push(value);
    }

    pub fn pop(&mut self) -> Option<String> {
        self.data.pop()
    }

    pub fn print(&self) {
        for item in self.data.iter().rev() {
            println!("{}", item);
        }
    }
}
