number_of_clients=$(tail -n +2 /etc/openvpn/server/easy-rsa/pki/index.txt | grep -c "^V")
if [[ "$number_of_clients" = 0 ]]; then
	echo
	echo "There are no existing clients!" > all_user.txt
	exit
fi
echo
tail -n +2 /etc/openvpn/server/easy-rsa/pki/index.txt | grep "^V" | cut -d '=' -f 2 | cat > all_users.txt