// -*- tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=8 sw=2 sts=2:

#ifndef DUNE_TYPETREE_TREEPATH_HH
#define DUNE_TYPETREE_TREEPATH_HH

#include <cstddef>

#include <dune/common/documentation.hh>
#include <dune/common/typetraits.hh>

#include <dune/typetree/fixedcapacitystack.hh>
#include <dune/typetree/utility.hh>


namespace Dune {
  namespace TypeTree {


    //! \addtogroup TreePath
    //! \ingroup TypeTree
    //! \{

    namespace TreePathType {
      enum Type { fullyStatic, mostlyStatic, dynamic };
    }

#if HAVE_VARIADIC_TEMPLATES || DOXYGEN

    template<std::size_t... i>
    struct TreePath {
      typedef TreePath ViewType;
      TreePath view() { return *this; }
      TreePath mutablePath() { return *this; }
    };

    template<typename>
    struct TreePathSize;

    template<std::size_t... i>
    struct TreePathSize<TreePath<i...> >
      : public integral_constant<std::size_t, sizeof...(i)>
    {};

    template<typename,std::size_t>
    struct TreePathPushBack;

    template<std::size_t k, std::size_t... i>
    struct TreePathPushBack<TreePath<i...>,k>
    {
      typedef TreePath<i...,k> type;
    };

    template<typename,std::size_t>
    struct TreePathPushFront;

    template<std::size_t k, std::size_t... i>
    struct TreePathPushFront<TreePath<i...>,k>
    {
      typedef TreePath<k,i...> type;
    };

    template<typename>
    struct TreePathBack;

    // There is only a single element, so return that...
    template<std::size_t k>
    struct TreePathBack<TreePath<k> >
      : public integral_constant<std::size_t,k>
    {};

    // We need to explicitly provide two elements here, as
    // the template argument pack would match the empty list
    // and create a conflict with the single-element specialization.
    // Here, we just shave off the first element and recursively
    // instantiate ourselves.
    template<std::size_t j, std::size_t k, std::size_t... l>
    struct TreePathBack<TreePath<j,k,l...> >
      : public TreePathBack<TreePath<k,l...> >
    {};

    template<typename>
    struct TreePathFront;

    template<std::size_t k, std::size_t... i>
    struct TreePathFront<TreePath<k,i...> >
      : public integral_constant<std::size_t,k>
    {};

    template<typename, std::size_t...>
    struct TreePathPopBack;

    template<std::size_t k, std::size_t... i>
    struct TreePathPopBack<TreePath<k>,i...>
    {
      typedef TreePath<i...> type;
    };

    template<std::size_t j,
             std::size_t k,
             std::size_t... l,
             std::size_t... i>
    struct TreePathPopBack<TreePath<j,k,l...>,i...>
      : public TreePathPopBack<TreePath<k,l...>,i...,j>
    {};

    template<typename>
    struct TreePathPopFront;

    template<std::size_t k, std::size_t... i>
    struct TreePathPopFront<TreePath<k,i...> >
    {
      typedef TreePath<i...> type;
    };

    template<typename, typename>
    struct TreePathConcat;

    template<std::size_t... i, std::size_t... k>
    struct TreePathConcat<TreePath<i...>,TreePath<k...> >
    {
      typedef TreePath<i...,k...> type;
    };

    template<std::size_t... i>
    void print_tree_path(std::ostream& os)
    {}

    template<std::size_t k, std::size_t... i>
    void print_tree_path(std::ostream& os)
    {
      os << k << " ";
      print_tree_path<i...>(os);
    }

    template<std::size_t... i>
    std::ostream& operator<<(std::ostream& os, const TreePath<i...>& tp)
    {
      os << "TreePath< ";
      print_tree_path<i...>(os);
      os << ">";
      return os;
    }

#else

    //! number used a dummy child number, similar to Nil
    /**
     * \note This should not be used directly, it is an implementation detail
     *       of class TreePath.
     */
    static const std::size_t noChildIndex = ~std::size_t(0);

    //! class used as a key to denote nodes in a tree
    /**
     * Class TreePath is a collection of indices.  It is like a tuple for
     * integral types instead of types.  Like a tuple, the number of entries
     * is not prescribed.
     *
     * Given a tree, class TreePath statically denotes one particular node
     * (subtree) in that tree.  That makes it possible for node visitors to
     * know exactly where in the tree they are, as opposed to only knowing the
     * type of the node they operate on.
     *
     * \note Due to limitations in the C++ language, the length of a tree path
     *       is arbitrarily limited to an implementation defined value
     *       (currently 10).  If this value is too restrictive, patches that
     *       extend it are welcome.
     */
    template<std::size_t i0 = noChildIndex, std::size_t i1 = noChildIndex,
             std::size_t i2 = noChildIndex, std::size_t i3 = noChildIndex,
             std::size_t i4 = noChildIndex, std::size_t i5 = noChildIndex,
             std::size_t i6 = noChildIndex, std::size_t i7 = noChildIndex,
             std::size_t i8 = noChildIndex, std::size_t i9 = noChildIndex>
    class TreePath {
      static_assert(i0 == noChildIndex ? i1 == noChildIndex : true,
                         "Only trailing indices my be noChildIndex");
      static_assert(i1 == noChildIndex ? i2 == noChildIndex : true,
                         "Only trailing indices my be noChildIndex");
      static_assert(i2 == noChildIndex ? i3 == noChildIndex : true,
                         "Only trailing indices my be noChildIndex");
      static_assert(i3 == noChildIndex ? i4 == noChildIndex : true,
                         "Only trailing indices my be noChildIndex");
      static_assert(i4 == noChildIndex ? i5 == noChildIndex : true,
                         "Only trailing indices my be noChildIndex");
      static_assert(i5 == noChildIndex ? i6 == noChildIndex : true,
                         "Only trailing indices my be noChildIndex");
      static_assert(i6 == noChildIndex ? i7 == noChildIndex : true,
                         "Only trailing indices my be noChildIndex");
      static_assert(i7 == noChildIndex ? i8 == noChildIndex : true,
                         "Only trailing indices my be noChildIndex");
      static_assert(i8 == noChildIndex ? i9 == noChildIndex : true,
                         "Only trailing indices my be noChildIndex");

      typedef TreePath ViewType;
      TreePath view() { return *this; }
      TreePath mutablePath() { return *this; }

    };

    //
    // The following classes operate on the front of a TreePath: They extract,
    // remove or prepend the first element.
    //

    //! remove first element of a tree path
    template<class TP>
    class TreePathPopFront {
      static_assert(AlwaysTrue<TP>::value,
                         "TreePathPopFront works on TreePaths only");
    public:
      //! The tree path with the first element removed
      typedef ImplementationDefined type;
    };

#ifndef DOXYGEN
    template<std::size_t i0, std::size_t i1, std::size_t i2, std::size_t i3,
             std::size_t i4, std::size_t i5, std::size_t i6, std::size_t i7,
             std::size_t i8, std::size_t i9>
    struct TreePathPopFront<TreePath<i0, i1, i2, i3, i4, i5, i6, i7, i8, i9> >
    {
      static_assert(i0 != noChildIndex,
                         "Can't pop first element from an empty TreePath");
      typedef TreePath<i1, i2, i3, i4, i5, i6, i7, i8, i9> type;
    };
#endif // DOXYGEN

    //! get first element of a tree path
    template<class TP>
    class TreePathFront {
      static_assert(AlwaysTrue<TP>::value,
                         "TreePathPopFront works on TreePaths only");
    public:
      //! value of the first element
      static const std::size_t value = implementationDefined;
    };

#ifndef DOXYGEN
    template<std::size_t i0, std::size_t i1, std::size_t i2, std::size_t i3,
             std::size_t i4, std::size_t i5, std::size_t i6, std::size_t i7,
             std::size_t i8, std::size_t i9>
    class TreePathFront<TreePath<i0, i1, i2, i3, i4, i5, i6, i7, i8, i9> > :
      public integral_constant<std::size_t, i0>
    {
      static_assert(i0 != noChildIndex,
                         "Can't take first element of an empty TreePath");
    };
#endif // DOXYGEN

    //! prepend one element to a tree path
    template<class TP, std::size_t i>
    class TreePathPushFront {
      static_assert(AlwaysTrue<TP>::value,
                         "TreePathPushFront works on TreePaths only");
    public:
      //! The tree path with i prepended
      typedef ImplementationDefined type;
    };

#ifndef DOXYGEN
    template<std::size_t i0, std::size_t i1, std::size_t i2, std::size_t i3,
             std::size_t i4, std::size_t i5, std::size_t i6, std::size_t i7,
             std::size_t i8, std::size_t i9, std::size_t i>
    struct TreePathPushFront<TreePath<i0, i1, i2, i3, i4, i5, i6, i7, i8, i9>,
                             i>
    {
      static_assert(i0 ? false : false, "TreePathPushFront: exceeded "
                         "implementation limit on TreePath size");
    };
    template<std::size_t i0, std::size_t i1, std::size_t i2, std::size_t i3,
             std::size_t i4, std::size_t i5, std::size_t i6, std::size_t i7,
             std::size_t i8, std::size_t i>
    struct TreePathPushFront<TreePath<i0, i1, i2, i3, i4, i5, i6, i7, i8>, i> {
      typedef TreePath<i, i0, i1, i2, i3, i4, i5, i6, i7, i8> type;
    };
#endif // DOXYGEN

    //
    // Using the front operations from above, is is easy to reverse an
    // arbitrary TreePath
    //

#ifdef DOXYGEN
    //! reverse a tree path
    template<class TP>
    class TreePathReverse {
    public:
      //! type of the reversed tree path
      typedef ImplementationDefined type;
    };
#else // !DOXYGEN
    template<class TP, class TP2 = TreePath<> >
    struct TreePathReverse :
      public TreePathReverse<
        typename TreePathPopFront<TP>::type,
        typename TreePathPushFront<TP2, TreePathFront<TP>::value>::type>
    { };
    template<class TP2>
    struct TreePathReverse<TreePath<>, TP2>
    { typedef TP2 type; };
#endif // DOXYGEN

    //
    // The following classes operate on the back of a TreePath: They extract,
    // remove or append the last element.  They are easy to implement using
    // the reverse operation.
    //

#ifdef DOXYGEN
    //! remove last element of a tree path
    template<class TP>
    struct TreePathPopBack {
      //! type of the tree path with the last element removed
      typedef ImplementationDefined type;
    };
#else // !DOXYGEN
    template<class TP>
    struct TreePathPopBack :
      public TreePathReverse<
        typename TreePathPopFront<typename TreePathReverse<TP>::type>::type
      >
    { };
#endif // DOXYGEN

#ifdef DOXYGEN
    //! get last element of a tree path
    template<class TP>
    struct TreePathBack {
      //! value of the last element
      static const std::size_t value = implementationDefined;
    };
#else // !DOXYGEN
    template<class TP>
    struct TreePathBack :
      public TreePathFront<typename TreePathReverse<TP>::type>
    { };
#endif // DOXYGEN

#ifdef DOXYGEN
    //! append one element to a tree path
    template<class TP, std::size_t i>
    struct TreePathPushBack {
      //! type of the tree path with i appended
      typedef ImplementationDefined type;
    };
#else // !DOXYGEN
    template<class TP, std::size_t i>
    struct TreePathPushBack :
      public TreePathReverse<
        typename TreePathPushFront<typename TreePathReverse<TP>::type, i>::type
      >
    { };
#endif // DOXYGEN

    //
    // Finally some tuple-like classes to determine the length of the TreePath
    // and to extract particular elements.
    //

#ifdef DOXYGEN
    //! determine size of a tree path
    template<class TP>
    struct TreePathSize {
      //! size of the tree path
      static const std::size_t value = implementationDefined;
    };
#else // !DOXYGEN
    template<class TP>
    struct TreePathSize :
      public integral_constant<
        std::size_t,
        TreePathSize<typename TreePathPopFront<TP>::type>::value+1
      >
    { };
    template<>
    struct TreePathSize<TreePath<> > :
      public integral_constant<std::size_t, 0>
    { };
#endif // DOXYGEN

#ifdef DOXYGEN
    //! extract a certain element of a path
    template<class TP>
    struct TreePathElement {
      //! value of the element
      static const std::size_t value = implementationDefined;
    };
#else // !DOXYGEN
    template<std::size_t pos, class TP>
    struct TreePathElement :
      public TreePathElement<pos-1, typename TreePathPopFront<TP>::type>
    { };
    template<class TP>
    struct TreePathElement<0, TP> :
      public TreePathFront<TP>
    { };
#endif // DOXYGEN


    template<typename, typename>
    struct TreePathConcat;

    template<typename TP1, typename TP2>
    struct TreePathConcat
    {
      typedef typename TreePathConcat<
        typename TreePathPushBack<
          TP1,
          TreePathFront<TP2>::value
          >::type,
        typename TreePathPopFront<TP2>::type
        >::type type;
    };

    template<typename TP1>
    struct TreePathConcat<TP1,TreePath<> >
    {
      typedef TP1 type;
    };

#endif // HAVE_VARIADIC_TEMPLATES


    //! A TreePath that stores the path of a node as runtime information.
    class DynamicTreePath
    {

    public:

      //! Get the size (length) of this path.
      std::size_t size() const
      {
        return _stack.size();
      }

      //! Get the index value at position pos.
      std::size_t element(std::size_t pos) const
      {
        return _stack[pos];
      }

      //! Get the last index value.
      std::size_t back() const
      {
        return _stack.back();
      }

      //! Get the first index value.
      std::size_t front() const
      {
        return _stack.front();
      }

      friend std::ostream& operator<<(std::ostream& os, const DynamicTreePath& tp)
      {
        os << "TreePath( ";
        for (std::size_t i = 0; i < tp.size(); ++i)
          os << tp.element(i) << " ";
        os << ")";
        return os;
      }

    protected:

#ifndef DOXYGEN

      typedef FixedCapacityStackView<std::size_t> Stack;

      Stack& _stack;

      DynamicTreePath(Stack& stack)
        : _stack(stack)
      {}

#endif // DOXYGEN

    };

#ifndef DOXYGEN // DynamicTreePath subclasses are implementation details and never exposed to the user

    // This is the object that gets passed around by the traversal algorithm. It
    // extends the DynamicTreePath with stack-like modifier methods. Note that
    // it does not yet allocate any storage for the index values. It just uses
    // the reference to a storage vector of the base class. This implies that all
    // objects that are copy-constructed from each other share a single index storage!
    // The reason for this is to avoid differentiating the visitor signature for static
    // and dynamic traversal: Having very cheap copy-construction for these objects
    // allows us to pass them by value.
    class MutableDynamicTreePath
      : public DynamicTreePath
    {

    public:

      typedef DynamicTreePath ViewType;

      void push_back(std::size_t v)
      {
        _stack.push_back(v);
      }

      void pop_back()
      {
        _stack.pop_back();
      }

      void set_back(std::size_t v)
      {
        _stack.back() = v;
      }

      DynamicTreePath view()
      {
        return *this;
      }

    protected:

      MutableDynamicTreePath(Stack& stack)
        : DynamicTreePath(stack)
      {}

    };

    // DynamicTreePath storage provider.
    // This objects provides the storage for the DynamicTreePath
    // during the tree traversal. After construction, it should
    // not be used directly - the traversal framework uses the
    // base class returned by calling mutablePath().
    template<std::size_t treeDepth>
    class MakeableDynamicTreePath
      : private FixedCapacityStack<std::size_t,treeDepth>
      , public MutableDynamicTreePath
    {

    public:

      MutableDynamicTreePath mutablePath()
      {
        return static_cast<MutableDynamicTreePath&>(*this);
      }

      MakeableDynamicTreePath()
        : MutableDynamicTreePath(static_cast<FixedCapacityStackView<std::size_t>&>(*this))
      {
      }

    };

    // Factory for creating the right type of TreePath based on the requested
    // traversal pattern (static or dynamic).
    template<TreePathType::Type tpType>
    struct TreePathFactory;

    // Factory for static traversal.
    template<>
    struct TreePathFactory<TreePathType::fullyStatic>
    {
      template<typename Tree>
      static TreePath<> create(const Tree& tree)
      {
        return TreePath<>();
      }
    };

    // Factory for dynamic traversal.
    template<>
    struct TreePathFactory<TreePathType::dynamic>
    {
      template<typename Tree>
      static MakeableDynamicTreePath<TreeInfo<Tree>::depth> create(const Tree& tree)
      {
        return MakeableDynamicTreePath<TreeInfo<Tree>::depth>();
      }
    };

#endif // DOXYGEN

    //! \} group TypeTree

  } // namespace TypeTree
} //namespace Dune

#endif // DUNE_TYPETREE_TREEPATH_HH
