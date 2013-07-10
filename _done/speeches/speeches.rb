# @q = quote
require 'yaml'

if ARGV.length != 2
	puts 'speeches type file'
	puts 'where type = latex, html'
	exit 1
end

if ARGV[0] == 'latex'
	type = :latex
elsif ARGV[0] == 'html'
	type = :html
else
	puts 'type = latex, html'
	exit 1
end

speeches = YAML.load(IO.read(ARGV[1]))
speeches.sort! { |x,y| x['date'].to_date <=> y['date'].to_date }

if type == :latex
	puts <<EOS
\\documentclass[a4paper]{amsbook}
\\usepackage[utf8]{inputenc}
\\usepackage[T1]{fontenc}
\\usepackage[pdftex]{graphicx}

\\title{Great Speeches}
\\author{Organization: Brett \\& Kate McKay \\\\
         Formatting: Andr\\'{e} Wagner}
\\date{}

\\begin{document}

\\maketitle
\\tableofcontents
EOS

	speeches.each do |sp|
		puts "\\chapter{#{sp['author']} - #{sp['name']}}\n\n"
		puts "\\textbf{\\Large{#{sp['place']} -- #{sp['date'].year < 100 ? '' : sp['date'].strftime('%B %d')+', '}#{sp['date'].year.abs} #{sp['date'].year < 0 ? 'B.C.' : '' }}}\n\n"
		puts "\\vspace{10 mm}\n\n"
		puts "\\begin{figure}\\includegraphics[width=0.6\\textwidth]{#{sp['image']}}\\end{figure}"
		puts "{\\em #{sp['description'].split("\n").join("\n\n")}}\n\n"
		puts "\\vspace{10 mm}\n\n"
		puts sp['speech'].gsub('$', '\$').gsub('...', '\ldots').gsub(/@q (.*)/, '\begin{quote}\1\end{quote}').split("\n").join("\n\n") + "\n\n"
		puts
	end

	puts "\\end{document}"

else
	puts <<EOS
<html>
	<head><title>Great Speeches</title><meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/></head>
	<body>
		<p align="center"><h1><center>Great Speeches<center></h1></p>
		<p align="center"><i>Organization: Brett & Kate McKay<br>Formatting: Andr&eacute; Wagner</i></p>
		<mbp:pagebreak/>
EOS
speeches.each do |sp|
	puts "<h2><a name=\"#{sp['link']}\">#{sp['author']} - #{sp['name']}</a></h2>"
	puts "<p><b>#{sp['place']} - #{sp['date'].year < 100 ? '' : sp['date'].strftime('%B %d')+', '}#{sp['date'].year.abs} #{sp['date'].year < 0 ? 'B.C.' : '' }</b></p>"
	puts "<img src=#{sp['image']}>"
	puts "<p><i>#{sp['description'].split("\n").join("</i></p><p><i>")}</i></p>"

	puts "<p>#{sp['speech'].gsub(/@q (.*)/, '<blockquote>\1</blockquote>').split("\n").join("</p><p>")}</p>"

	puts "<mbp:pagebreak/>"
end
	puts <<EOS
	</body>
</html>
EOS
end
