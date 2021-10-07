module yaml_types
  use iso_c_binding
  implicit none
  
  integer,parameter :: string_length = 1024
  
  type type_node_c
    
    ! Node
    integer(c_int) :: T
    ! character(len=string_length, kind=c_char) :: path 
    
    ! Scalar
    type(c_ptr) :: string = c_null_ptr
    
    ! Dictionary
    type(c_ptr) :: first_keyvaluepair = c_null_ptr
    type(c_ptr) :: key = c_null_ptr
    type(c_ptr) :: value = c_null_ptr
    type(c_ptr) :: next_keyvaluepair = c_null_ptr
    
    ! List
    type(c_ptr) :: first_listitem = c_null_ptr
    type(c_ptr) :: node = c_null_ptr
    type(c_ptr) :: next_listitem = c_null_ptr
  end type
  
  interface
    function LoadFile_c(filename) result(ptr) bind(C, name="LoadFile_c")
      use, intrinsic :: iso_c_binding
      character(len=1, kind = c_char) :: filename
      type(c_ptr) :: ptr
    end function
    
    subroutine DestroyNode(root) bind(C, name="DestroyNode")
      use, intrinsic :: iso_c_binding
      type(c_ptr), intent(inout) :: root
    end subroutine
  end interface
  
contains
  
  function LoadFile(filename) result(root)
    character(len=*), intent(in) :: filename
    type(c_ptr) :: root
    character(len=:, kind=c_char), allocatable :: filename_copy
    filename_copy = filename//char(0)
    root = LoadFile_c(filename_copy)
    deallocate(filename_copy)
  end function
  
  subroutine test()
    
    type(c_ptr) :: ptr, root
    type(type_node_c), pointer :: node_c, item_c
    character(len=string_length, kind=c_char), pointer :: string

    root = LoadFile("../test.yaml")
    call DestroyNode(root)

  end subroutine
  
  
end module