
ONLINE TRANSACTION PROCESSING:
	Let us look at the saving bank accounting in a Bank. We can have a single file as the master file that contains a set of fixed length records, one record per account.  The unique identification of an account is simply the record number itself. Possible transactions ( that we would like to execute concurrently from several terminals ):
	* Create account: addition of new record into the file
	* Delete account:
				Since it is not possible to remove a set of bytes from the middle of the file, we can simply keep a record active/ inactive flag as one of the field. We would not like the record numbers to be changed by purging inactive records.  This means that we could use the record number itself as the account number.
	* Deposit : A specified amount to a specified account number.
	* Withdraw : some amount from an account, if possible.
	* Display : The current balance in an account.
	* Change of Address : (or, say, phone number ).

