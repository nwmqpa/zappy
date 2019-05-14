package main

type Direction int

const (
    Left = 0
    Right = 1
    Up = 2
    Down = 3
)

type Item int

type Inventory struct {
    Items []Item
}

type Player struct {
    Direction int
    Inventory Inventory
}