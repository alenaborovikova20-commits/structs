use std::collections::VecDeque;
use std::io::{self, Write};

type Link = Option<Box<ANode>>;

pub struct ANode {
    pub key: i32,
    pub left: Link,
    pub right: Link,
    pub height: i32,
}

pub struct AvlTree {
    pub root: Link,
}

impl AvlTree {
    pub fn new() -> Self {
        AvlTree { root: None }
    }

    fn height(node: &Link) -> i32 {
        node.as_ref().map_or(0, |n| n.height)
    }

    fn update_height(node: &mut ANode) {
        node.height = 1 + Self::height(&node.left).max(Self::height(&node.right));
    }

    fn balance_factor(node: &ANode) -> i32 {
        Self::height(&node.left) - Self::height(&node.right)
    }

    fn rotate_right(mut y: Box<ANode>) -> Box<ANode> {
        let mut x = y.left.take().unwrap();
        y.left = x.right.take();
        Self::update_height(&mut y);
        x.right = Some(y);
        Self::update_height(&mut x);
        x
    }

    fn rotate_left(mut x: Box<ANode>) -> Box<ANode> {
        let mut y = x.right.take().unwrap();
        x.right = y.left.take();
        Self::update_height(&mut x);
        y.left = Some(x);
        Self::update_height(&mut y);
        y
    }

    fn balance(mut node: Box<ANode>) -> Box<ANode> {
        Self::update_height(&mut node);
        let bf = Self::balance_factor(&node);
        if bf > 1 {
            let left_bf = node.left.as_ref().map_or(0, |n| Self::balance_factor(n));
            if left_bf < 0 {
                let left = node.left.take().unwrap();
                node.left = Some(Self::rotate_left(left));
            }
            return Self::rotate_right(node);
        }
        if bf < -1 {
            let right_bf = node.right.as_ref().map_or(0, |n| Self::balance_factor(n));
            if right_bf > 0 {
                let right = node.right.take().unwrap();
                node.right = Some(Self::rotate_right(right));
            }
            return Self::rotate_left(node);
        }
        node
    }

    fn insert(node: Link, key: i32) -> Link {
        match node {
            None => Some(Box::new(ANode {
                key,
                left: None,
                right: None,
                height: 1,
            })),
            Some(mut n) => {
                if key < n.key {
                    n.left = Self::insert(n.left.take(), key);
                } else if key > n.key {
                    n.right = Self::insert(n.right.take(), key);
                } else {
                    return Some(n);
                }
                Some(Self::balance(n))
            }
        }
    }

    fn find_min(mut node: Box<ANode>) -> Box<ANode> {
        while node.left.is_some() {
            node = node.left.take().unwrap();
        }
        node
    }

    fn remove(node: Link, key: i32) -> Link {
        let mut n = match node {
            None => return None,
            Some(n) => n,
        };
        if key < n.key {
            n.left = Self::remove(n.left.take(), key);
        } else if key > n.key {
            n.right = Self::remove(n.right.take(), key);
        } else {
            if n.left.is_none() {
                return n.right;
            }
            if n.right.is_none() {
                return n.left;
            }
            let successor = Self::find_min(n.right.take().unwrap());
            n.key = successor.key;
            n.right = Self::remove(n.right.take(), successor.key);
        }
        Some(Self::balance(n))
    }

    fn search(node: &Link, key: i32) -> bool {
        match node {
            None => false,
            Some(n) => {
                if key == n.key {
                    true
                } else if key < n.key {
                    Self::search(&n.left, key)
                } else {
                    Self::search(&n.right, key)
                }
            }
        }
    }

    pub fn insert_key(&mut self, key: i32) {
        self.root = Self::insert(self.root.take(), key);
    }

    pub fn del(&mut self, key: i32) {
        self.root = Self::remove(self.root.take(), key);
    }

    pub fn get(&self, key: i32) -> bool {
        Self::search(&self.root, key)
    }

    pub fn print(&self) {
        if self.root.is_none() {
            return;
        }
        let mut q = VecDeque::new();
        q.push_back(self.root.as_ref().unwrap());
        while let Some(cur) = q.pop_front() {
            print!("{} ", cur.key);
            if let Some(l) = &cur.left {
                q.push_back(l);
            }
            if let Some(r) = &cur.right {
                q.push_back(r);
            }
        }
        println!();
    }

    fn save_pre(node: &Link, out: &mut String) {
        if let Some(n) = node {
            out.push_str(&format!("{} ", n.key));
            Self::save_pre(&n.left, out);
            Self::save_pre(&n.right, out);
        }
    }

    fn count_nodes(node: &Link) -> usize {
        match node {
            None => 0,
            Some(n) => 1 + Self::count_nodes(&n.left) + Self::count_nodes(&n.right),
        }
    }

    pub fn save<W: Write>(&self, out: &mut W) -> io::Result<()> {
        let count = Self::count_nodes(&self.root);
        writeln!(out, "{}", count)?;
        let mut buf = String::new();
        Self::save_pre(&self.root, &mut buf);
        writeln!(out, "{}", buf.trim_end())?;
        Ok(())
    }

    pub fn load(&mut self, input: &str) -> Result<(), String> {
        self.root = None;
        let mut lines = input.lines();
        let count: usize = lines.next().ok_or("Нет данных")?
            .trim().parse().map_err(|_| "Ошибка размера")?;
        if count == 0 {
            return Ok(());
        }
        let data = lines.next().ok_or("Нет данных")?;
        for token in data.split_whitespace().take(count) {
            let v: i32 = token.parse().map_err(|_| "Ошибка числа")?;
            self.insert_key(v);
        }
        Ok(())
    }
}