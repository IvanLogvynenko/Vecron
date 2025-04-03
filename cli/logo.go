package cli

import "fmt"

func PrintLogo() {
	logo := []string{
		"\t\t\t\t╔══════════════════════════════════════════════════════╗",
		"\t\t\t\t║ ██╗   ██╗███████╗ ██████╗██████╗  ██████╗ ███╗   ██╗ ║",
		"\t\t\t\t║ ██║   ██║██╔════╝██╔════╝██╔══██╗██╔═══██╗████╗  ██║ ║",
		"\t\t\t\t║ ██║   ██║█████╗  ██║     ██████╔╝██║   ██║██╔██╗ ██║ ║",
		"\t\t\t\t║ ╚██╗ ██╔╝██╔══╝  ██║     ██╔══██╗██║   ██║██║╚██╗██║ ║",
		"\t\t\t\t║  ╚████╔╝ ███████╗╚██████╗██║  ██║╚██████╔╝██║ ╚████║ ║",
		"\t\t\t\t║   ╚═══╝  ╚══════╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝ ║",
		"\t\t\t\t╚══════════════════════════════════════════════════════╝",
	}
	for _, line := range logo {
		fmt.Println(line)
	}
}
