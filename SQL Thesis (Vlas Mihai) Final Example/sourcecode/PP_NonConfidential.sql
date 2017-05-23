Create view vwNonConfidentialEmployees
as
SELECT Id, Name, Gender, DeptName
from tblEmployee
join tblDepartment
on tblEmployee.DepartmentId=tblDepartment.DeptId

GO
Select * from vwNonConfidentialEmployees

