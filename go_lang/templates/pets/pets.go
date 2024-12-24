package main

import (
	"os"
	"text/template"
)

type Pet struct {
	Name   string
	Sex    string
	Intact bool
	Age    string
	Breed  string
}

func main() {
	dogs := []Pet{
		{
			Name:   "Jujube",
			Sex:    "Female",
			Intact: false,
			Age:    "10 months",
			Breed:  "German Shepherd/Pitbull",
		},
		{
			Name:   "Zephyr",
			Sex:    "Male",
			Intact: true,
			Age:    "13 years, 3 months",
			Breed:  "German Shepherd/Border Collie",
		},
		{
			Name:	"Bruce Wayne",
			Sex:	"Male",
			Intact:	false,
			Age:	"3 years, 8 months",
			Breed:	"Chihuahua",
		},
	}
	funcMap := template.FuncMap{
		"dec": func(i int) int { return i - 1 },
	}
	var tmplFile = "pets.tmpl"
	tmpl, err := template.New(tmplFile).ParseFiles(tmplFile)
	if err != nil {
		panic(err)
	}
	err = tmpl.Execute(os.Stdout, dogs)
	if err != nil {
		panic(err)
	}
} // end main
