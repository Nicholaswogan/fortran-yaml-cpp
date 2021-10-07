module yaml_types
  use iso_c_binding
  implicit none
  
  integer,parameter :: string_length = 1024
  
  type type_node_c
    integer(c_int) :: T
    
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
    function LoadFile_c() result(ptr) bind(C, name="LoadFile_c")
        use, intrinsic :: iso_c_binding
        type(c_ptr) :: ptr
    end function
  end interface
  
contains
  
  subroutine test2()
    
    type(c_ptr) :: ptr = c_null_ptr
    type(type_node_c), pointer :: node_c, item_c
    character(len=string_length, kind=c_char), pointer :: string
    
    ptr = LoadFile_c()
    call c_f_pointer(ptr, node_c)
    
    
    
    ptr = node_c%first_keyvaluepair
    call c_f_pointer(ptr, item_c)
    ptr = item_c%value
    call c_f_pointer(ptr, node_c)
    ptr = node_c%first_keyvaluepair
    call c_f_pointer(ptr, item_c)
    ptr = item_c%value
    call c_f_pointer(ptr, node_c)
    
    
    ptr = node_c%first_listitem
    call c_f_pointer(ptr, item_c)
    ptr = item_c%node
    call c_f_pointer(ptr, node_c)

    ptr = node_c%string
    call c_f_pointer(ptr, string)
    print*,string

  end subroutine
  
  
  
end module