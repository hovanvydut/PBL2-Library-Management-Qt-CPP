-- Trigger update
CREATE TRIGGER userUpdate
ON dbo.users
AFTER UPDATE 
AS BEGIN
   UPDATE dbo.users
   SET updated_at = GETDATE()
   FROM INSERTED new
   WHERE new.user_id = users.user_id
END