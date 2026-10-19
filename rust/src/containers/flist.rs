pub type Link = Option<Box<Node>>;

pub struct Node {
    pub key: String,
    pub next: Link,
}

pub struct Flist {
    pub head: Link,
}

impl Flist {
    pub fn new() -> Self {
        Flist { head: None }
    }

    pub fn push(&mut self, key: String) {
        let new_node = Box::new(Node {
            key,
            next: self.head.take(),
        });
        self.head = Some(new_node);
    }

    pub fn del(&mut self, target: &str) {
        let mut current = &mut self.head;
        while let Some(node) = current {
            if node.key == target {
                *current = node.next.take();
                return;
            }
            current = &mut current.as_mut().unwrap().next;
        }
    }

    pub fn contains(&self, target: &str) -> bool {
        let mut current = &self.head;
        while let Some(node) = current {
            if node.key == target {
                return true;
            }
            current = &node.next;
        }
        false
    }

    pub fn print(&self) {
        let mut current = &self.head;
        while let Some(node) = current {
            print!("{} ", node.key);
            current = &node.next;
        }
        println!();
    }
}
