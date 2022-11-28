SET SERVEROUTPUT ON;

DECLARE
    accno int := &accno;
    minbal int := &minbal;
BEGIN
    FOR acc IN (SELECT * FROM account WHERE account_number = accno) LOOP
        dbms_output.put_line('Current balance is ' || acc.balance);
        IF (acc.balance < minbal) THEN
            dbms_output.put_line('Less than minimum balance. Deducting 100!!');
            UPDATE account SET balance=(acc.balance-100) WHERE account_number=accno;
        END IF;
    END LOOP;
END;
/