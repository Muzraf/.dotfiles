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

len=0
paths[$len]="$PWD"
len=$((len + 1))
paths[$len]="$HOME/storage/downloads"
len=$((len + 1))
if [ -f ~/.dir-last ]; then
	lines=$(wc ~/.dir-last --lines | cut -f1 -d " ")
	for ((i=1;i<=$lines;i++)); do
		paths[len]="$(cat ~/.dir-last | tail -n -$i | head -n 1)"
		len=$((len + 1))
	done
fi

for ((i=0;i<len-1;i++));do

	if [[ ${paths[i]} == "" ]]; then
		continue;
	fi
	for ((j=i+1;j<len;j++));do
		if [[ ${paths[i]} == ${paths[j]} ]]; then
			unset paths[$j];
		fi
	done;
done;
j=0;
for ((i=0;i<len;i++)); do
	if [[ ${paths[i]} == "" ]]; then
		continue;
	fi
	if [ $i -gt $j ]; then
		paths[$j]=${paths[i]}
	fi
	j=$((j+1))
done;
len=$j;
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
	if [[ $@ =~ .*"-target".* ]]; then
		command zig $@
	else
		command zig $@ -target aarch64-linux-musl
	fi
		
}
