
use std::rc::Rc;
use std::cell::RefCell;

type Link = Option<Rc<RefCell<Node>>>;

pub struct Node {
    pub key: String,
    pub prev: Link,
    pub next: Link,
}

pub struct Dlist {
    pub head: Link,
}

impl Dlist {
    pub fn new() -> Self {
        Dlist { head: None }
    }

    pub fn push(&mut self, key: String) {
        let new_node = Rc::new(RefCell::new(Node {
            key,
            prev: None,
            next: self.head.clone(),
        }));
        if let Some(old_head) = &self.head {
            old_head.borrow_mut().prev = Some(new_node.clone());
        }
        self.head = Some(new_node);
    }

    pub fn del(&mut self, target: &str) {
        let mut current = self.head.clone();
        while let Some(node_rc) = current {
            if node_rc.borrow().key == target {
                let prev = node_rc.borrow().prev.clone();
                let next = node_rc.borrow().next.clone();

                if let Some(ref p) = prev {
                    p.borrow_mut().next = next.clone();
                } else {
                    self.head = next.clone();
                }
                if let Some(n) = next {
                    n.borrow_mut().prev = prev;
                }
                return;
            }
            let next = node_rc.borrow().next.clone();
            current = next;
        }
    }

    pub fn contains(&self, target: &str) -> bool {
        let mut current = self.head.clone();
        while let Some(node_rc) = current {
            if node_rc.borrow().key == target {
                return true;
            }
            let next = node_rc.borrow().next.clone();
            current = next;
        }
        false
    }

    pub fn print(&self) {
        let mut current = self.head.clone();
        while let Some(node_rc) = current {
            print!("{} ", node_rc.borrow().key);
            let next = node_rc.borrow().next.clone();
            current = next;
        }
        println!();
    }
}
