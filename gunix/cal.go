package main

import (
	"flag"
	"fmt"
	"log"
	"strconv"
	"time"
)

const (
	_ = iota
	single
	full
)


var month = time.Now().Month()
var year = time.Now().Year()
var display int


func main() {
	parseFlags()
	if display == single {
		showCalendar(month, year)
	} else {
		for i := 1; i <= 12; i++ { showCalendar(time.Month(i), year) }
	}
}


func parseFlags() {
	display = single

	flag.Parse()
	switch len(flag.Args()) {
	case 0:
	case 1:
		y, err := strconv.ParseInt(flag.Args()[0], 10, 0)
		if err != nil { log.Fatal(err) }
		year = int(y)
		display = full
	case 2:
		m, err := strconv.ParseInt(flag.Args()[0], 10, 0)
		if err != nil { log.Fatal(err) }
		if m < 1 || m > 12 { 
			log.Fatal("month must be between 1 and 12") 
		}
		y, err := strconv.ParseInt(flag.Args()[1], 10, 0) 
		if err != nil { log.Fatal(err) }
		month, year = time.Month(m), int(y)
	default:
		log.Fatal("wrong number of arguments")
	}
}


func showCalendar(month time.Month, year int) {
	fmt.Printf("%s %v\n", month, year)
	fmt.Println(" Su Mo Tu We Th Fr Sa")
	daysInMonth := time.Date(year, month+1, 1, 0, 0, 0, 0, time.UTC).AddDate(0, 0, -1).Day()
	firstWeekday := time.Date(year, month, 1, 0, 0, 0, 0, time.UTC).Weekday()
	show := false
	weekday := time.Sunday
	for day := 1; day <= daysInMonth ; {
		if !show {
			if weekday < firstWeekday {
				fmt.Printf("   ")
			} else {
				show = true
			}
		}
		if show {
			star := " "
			ny, nm, nd := time.Now().Date()
			if ny == year && nm == month && nd == day {
				star = ">"
			}
			fmt.Printf("%s%2d", star, day)
			day++
		}
		weekday++
		if weekday > 6 { 
			weekday = time.Sunday
			fmt.Println()
		}
	}
	fmt.Println()
	fmt.Println()
}
