USE LibraryManagement

CREATE TRIGGER deleteRole
ON roles 
AFTER DELETE
AS BEGIN
	DECLARE @maxPriorty INT
	DECLARE @roleIdMax INT
	SELECT @maxPriorty=MAX(priorty) FROM roles
	SELECT @roleIdMax = role_id FROM roles WHERE priorty = @maxPriorty
	UPDATE users SET role_id = @roleIdMax WHERE role_id IS NULL
END

