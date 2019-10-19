# scritp for pushing 

branch=$(git branch | grep "*" | cut -d ' ' -f 2)
echo "push in $branch branch?"
read answer
if [ $answer == "Y" ]; then
	git push github $branch;
        git push github $branch;
fi
