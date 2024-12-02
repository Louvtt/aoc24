make "bin/${1}-exe" # rebuild everything
exec "./bin/${1}-exe-p${3}" "${1}/${2}.txt"
