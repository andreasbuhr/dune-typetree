// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:

#ifndef DUNE_TYPETREE_SIMPLETRANSFORMATIONDESCRIPTORS_HH
#define DUNE_TYPETREE_SIMPLETRANSFORMATIONDESCRIPTORS_HH

#include <dune/typetree/nodetags.hh>
#include <dune/common/exceptions.hh>
#include <dune/common/shared_ptr.hh>
#include <dune/common/array.hh>
#include <dune/common/tuples.hh>


namespace Dune {
  namespace TypeTree {

    /** \addtogroup Transformation
     *  \ingroup TypeTree
     *  \{
     */

    template<typename SourceNode, typename Transformation, typename TransformedNode>
    struct SimpleLeafNodeTransformation
    {

      static const bool recursive = false;

      typedef TransformedNode transformed_type;
      typedef shared_ptr<transformed_type> transformed_storage_type;

      static transformed_type transform(const SourceNode& s, const Transformation& t)
      {
        return transformed_type();
      }

      static transformed_storage_type transform_storage(shared_ptr<const SourceNode> s, const Transformation& t)
      {
        return make_shared<transformed_type>();
      }

    };


    template<typename SourceNode, typename Transformation, template<typename Child, std::size_t> class TransformedNode>
    struct SimplePowerNodeTransformation
    {

      static const bool recursive = true;

      template<typename TC>
      struct result
      {
        typedef TransformedNode<TC, SourceNode::CHILDREN> type;
        typedef shared_ptr<type> storage_type;
      };

      template<typename TC>
      static typename result<TC>::type transform(const SourceNode& s, const Transformation& t, const array<shared_ptr<TC>,result<TC>::type::CHILDREN>& children)
      {
        return typename result<TC>::type(children);
      }

      template<typename TC>
      static typename result<TC>::storage_type transform_storage(shared_ptr<const SourceNode> s, const Transformation& t, const array<shared_ptr<TC>,result<TC>::type::CHILDREN>& children)
      {
        return make_shared<typename result<TC>::type>(children);
      }

    };


#if HAVE_VARIADIC_TEMPLATES

    template<typename SourceNode, typename Transformation, template<typename...> class TransformedNode>
    struct SimpleVariadicCompositeNodeTransformation
    {

      static const bool recursive = true;

      template<typename... TC>
      struct result
      {
        typedef TransformedNode<TC...> type;
        typedef shared_ptr<type> storage_type;
      };

      template<typename... TC>
      static typename result<TC...>::type transform(const SourceNode& s, const Transformation& t, shared_ptr<TC>... children)
      {
        return typename result<TC...>::type(children...);
      }

      template<typename... TC>
      static typename result<TC...>::storage_type transform_storage(shared_ptr<const SourceNode> s, const Transformation& t, shared_ptr<TC>... children)
      {
        return make_shared<typename result<TC...>::type>(children...);
      }

    };

#endif // HAVE_VARIADIC_TEMPLATES


    template<typename SourceNode, typename Transformation, template<typename C0,
                                                                    typename C1,
                                                                    typename C2,
                                                                    typename C3,
                                                                    typename C4,
                                                                    typename C5,
                                                                    typename C6,
                                                                    typename C7,
                                                                    typename C8,
                                                                    typename C9
                                                                    > class TransformedNode>
    struct SimpleCompositeNodeTransformation
    {

      static const bool recursive = true;

      template<typename TC0,
               typename TC1,
               typename TC2,
               typename TC3,
               typename TC4,
               typename TC5,
               typename TC6,
               typename TC7,
               typename TC8,
               typename TC9>
      struct result
      {
        typedef TransformedNode<TC0,TC1,TC2,TC3,TC4,TC5,TC6,TC7,TC8,TC9> type;
        typedef shared_ptr<type> storage_type;
      };

      template<typename TC0,
               typename TC1,
               typename TC2,
               typename TC3,
               typename TC4,
               typename TC5,
               typename TC6,
               typename TC7,
               typename TC8,
               typename TC9>
      static typename result<TC0,TC1,TC2,TC3,TC4,TC5,TC6,TC7,TC8,TC9>::type
      transform(const SourceNode& s,
                const Transformation& t,
                shared_ptr<TC0> c0,
                shared_ptr<TC1> c1,
                shared_ptr<TC2> c2,
                shared_ptr<TC3> c3,
                shared_ptr<TC4> c4,
                shared_ptr<TC5> c5,
                shared_ptr<TC6> c6,
                shared_ptr<TC7> c7,
                shared_ptr<TC8> c8,
                shared_ptr<TC9> c9)
      {
        return typename result<TC0,TC1,TC2,TC3,TC4,TC5,TC6,TC7,TC8,TC9>::type(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9);
      }

      template<typename TC0,
               typename TC1,
               typename TC2,
               typename TC3,
               typename TC4,
               typename TC5,
               typename TC6,
               typename TC7,
               typename TC8,
               typename TC9>
      static typename result<TC0,TC1,TC2,TC3,TC4,TC5,TC6,TC7,TC8,TC9>::storage_type
      transform_storage(shared_ptr<const SourceNode> s,
                        const Transformation& t,
                        shared_ptr<TC0> c0,
                        shared_ptr<TC1> c1,
                        shared_ptr<TC2> c2,
                        shared_ptr<TC3> c3,
                        shared_ptr<TC4> c4,
                        shared_ptr<TC5> c5,
                        shared_ptr<TC6> c6,
                        shared_ptr<TC7> c7,
                        shared_ptr<TC8> c8,
                        shared_ptr<TC9> c9)
      {
        return make_shared<typename result<TC0,TC1,TC2,TC3,TC4,TC5,TC6,TC7,TC8,TC9>::type>(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9);
      }

    };

    //! \} group Transformation

  } // namespace TypeTree
} //namespace Dune

#endif // DUNE_TYPETREE_SIMPLETRANSFORMATIONDESCRIPTORS_HH
