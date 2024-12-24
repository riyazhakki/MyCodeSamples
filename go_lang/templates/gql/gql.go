package main

import (
	"bytes"
	"flag"
	"fmt"
	"log"
	"strings"
	"text/template"
)

type JobSubmitArguments struct {
	Walltime string
	Queue    string
	Project  string
}

// parseJobSubmitArgs receives job submit argument and parse,
// validates and return in a struct
func parseJobSubmitArgs(jobparams string) JobSubmitArguments {

	// Split the config parameter into arguments
	args := strings.Fields(jobparams)
	jargs := JobSubmitArguments{}

	// Use flag package to define custom flags
	flagSet := flag.NewFlagSet("options", flag.ContinueOnError)

	// Currently supporting the following three arguments; more can be added here.
	flagSet.StringVar(&jargs.Walltime, "lwalltime", "", "Set the walltime (e.g., 1:00:00)")
	flagSet.StringVar(&jargs.Queue, "q", "", "Specify the queue (e.g., workq)")
	flagSet.StringVar(&jargs.Project, "P", "", "Specify the project (e.g., myproject)")

	// Parse the arguments
	err := flagSet.Parse(args)
	if err != nil {
		log.Fatalf("Failed to parse job submit arguments: %v", err)
	}

	return jargs
}

func main() {

	jobsubparam := "-lwalltime=1:00:00 -q myworkq -P myproject"
	funcMap := template.FuncMap{
		"IsNotEmpty": func(m string) bool {
			return len(m) != 0
		},
	}

	jobargs := parseJobSubmitArgs(jobsubparam)

	var output bytes.Buffer
	var tmplFile = "createJobGql.tmpl"
	tmpl, err := template.New(tmplFile).Funcs(funcMap).ParseFiles(tmplFile)
	if err != nil {
		panic(err)
	}
	err = tmpl.Execute(&output, jobargs)
	if err != nil {
		panic(err)
	}

	base64String := "jobscript"
	DefaultUser := "pbsk8sconnector"
	IdleNodeTime := 60
	dpns := "kube-system"
	LogLevel := "info"
	cpus := 3
	memroy := "1024"
	gpus := 0

	query := fmt.Sprintf(output.String(), base64String, DefaultUser, int(IdleNodeTime), dpns, LogLevel, cpus, memroy, gpus)
	fmt.Println(query)
}
