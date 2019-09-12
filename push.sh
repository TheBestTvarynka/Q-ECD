# scritp for pushing 

branch = $($(git branch | grep "*" | cut -d ' ' -f 2))
echo $branch
