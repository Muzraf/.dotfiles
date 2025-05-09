columns=$(tput cols)

function char_print_full {
	for ((i=0;i<columns;i++)); do
		echo -n $@
	done;
	echo
}

char_print_full "="
echo
fortune | fold -w $columns -s
echo
char_print_full "="

dirlast

len=0
if [ -f ~/.dir-last ]; then
	lines=$(wc ~/.dir-last --lines | cut -f1 -d " ")
	for ((i=1;i<=$lines;i++)); do
		paths[len]="$(cat ~/.dir-last | head -n $i | tail -n -1)"
		len=$((len + 1))
	done
fi

n=$((len**3));
c=-1
for ((i=0;i<=len;i++));do
	echo
done;
tput rmam
tput civis
stty -echo
for ((i=0;i<=n;i++)); do
	c=$((c+1))
	c=$((c%len))
	tput cuu $((len+1))
	echo $((n-i))
	for ((j=0;j<len;j++)); do
		if [ $j -eq $c ];then
			tput setab 7
			tput setaf 0
		fi
		echo $(to-env -c $columns "${paths[j]}")
		if [ $j -eq $c ];then
			tput sgr0
		fi
	done;
	read -t 1 -n1
	if [ $? -eq 0 ]; then
		break;
	fi
done;
stty echo
tput cnorm
tput smam
cd "${paths[c]}"
ls

zig() {
	if [[ $@ =~ .*"init".* ]]; then
		command zig $@
		return
	fi
	if [[ $@ =~ .*"-target".* ]]; then
		command zig $@
	else
		command zig $@ -target aarch64-linux-musl
	fi
}

dcd() {
	if [ $# -eq 0 ]; then
		cat ~/.dir-last
		return
	fi
	if [ $1 -eq 0 ]; then
		cd ~/storage/downloads
		return
	fi
	cd $(head ~/.dir-last -n $1 | tail -n -1)
}

alias cd..='cd ..'
