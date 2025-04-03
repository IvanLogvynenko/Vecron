package utils

import (
	"fmt"
)

// Simple key-value storage
type DataBase struct {
	kv map[string]string
}

var database *DataBase = nil

func GetDataBaseInstance() *DataBase {
	if database == nil {
		database = &DataBase{}
		database.kv = make(map[string]string)
	}
	return database
}

func (db DataBase) Get(key string) (string, error) {
	data := db.kv[key]
	if data != "" {
		return data, nil
	} else {
		return "", fmt.Errorf("data not found")
	}
}

func (db *DataBase) Set(key string, value string) {
	db.kv[key] = value
}

func (db *DataBase) Delete(key string) {
	_, err := db.Get(key)
	if err != nil {
		panic(err)
	}
	delete(db.kv, key)
}

func (db DataBase) Print() {
	fmt.Println("DataBase dump:")
	for k, v := range db.kv {
		fmt.Println(k, ": ", v)
	}
	fmt.Println("______________")
}
