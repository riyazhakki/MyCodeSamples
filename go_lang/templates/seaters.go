package main

import (
	"os"
	"text/template"
)

func main() {
	type Inventory struct {
		Material string
		Count    uint
	}
	type Inventory2 struct {
		Material string
		Count    uint
	}
	sweaters := Inventory{"wool", 17}
	sweaters2 := Inventory2{"wool", 19}
	tmpl, err := template.New("test").Parse("{{.Count}} items are made of {{.Material}}")
	if err != nil {
		panic(err)
	}
	err = tmpl.Execute(os.Stdout, sweaters)
	if err != nil {
		panic(err)
	}
	err = tmpl.Execute(os.Stdout, sweaters2)
	if err != nil {
		panic(err)
	}
}
