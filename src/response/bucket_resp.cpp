// Copyright (c) 2017, Tencent Inc.
// All rights reserved.
//
// Author: sevenyou <sevenyou@tencent.com>
// Created: 07/17/17
// Description:

#include "response/bucket_resp.h"

#include "rapidxml/1.13/rapidxml.hpp"
#include "rapidxml/1.13/rapidxml_print.hpp"
#include "rapidxml/1.13/rapidxml_utils.hpp"

#include "cos_params.h"
#include "cos_sys_config.h"
#include "util/string_util.h"

namespace qcloud_cos {

bool GetBucketResp::ParseFromXmlString(const std::string& body) {
    rapidxml::xml_document<> doc;
    if (!StringUtil::StringToXml(body, &doc)) {
        SDK_LOG_ERR("Parse string to xml doc error, xml_body=%s", body.c_str());
        return false;
    }

    rapidxml::xml_node<>* root = doc.first_node(kGetBucketRoot.c_str());
    if (NULL == root) {
        SDK_LOG_ERR("Miss root node=ListBucketResult, xml_body=%s", body.c_str());
        return false;
    }

    rapidxml::xml_node<>* node = root->first_node();
    for (; node != NULL; node = node->next_sibling()) {
        const std::string& node_name = node->name();
        if (node_name == kGetBucketName) {
            m_name = node->value();
        } else if (node_name == kGetBucketEncodingType) {
            m_encoding_type = node->value();
        } else if (node_name == kGetBucketNextMarker) {
            m_next_marker = node->value();
        } else if (node_name == kGetBucketDelimiter) {
            m_delimiter = node->value();
        } else if (node_name == kGetBucketPrefix) {
            m_prefix = node->value();
        } else if (node_name == kGetBucketMarker) {
            m_marker = node->value();
        } else if (node_name == kGetBucketMaxKeys) {
            m_max_keys = StringUtil::StringToUint64(node->value());
        } else if (node_name == kGetBucketIsTruncated) {
            m_is_truncated = ("true" == node->value()) ? true : false;
        } else if (node_name == kGetBucketCommonPrefixes) {
            rapidxml::xml_node<>* common_prefix_node = node->first_node();
            for (; common_prefix_node != NULL;
                 common_prefix_node = common_prefix_node->next_sibling()) {
                m_common_prefixes.push_back(node->value());
            }
        } else if (node_name == kGetBucketContents) {
            rapidxml::xml_node<>* contents_node = node->first_node();
            Content cnt;
            for (; contents_node != NULL; contents_node = contents_node->next_sibling()) {
                const std::string name = contents_node->name();
                if (name == kGetBucketContentsKey) {
                    cnt.m_key = contents_node->value();
                } else if (name == kGetBucketContentsLastModified) {
                    cnt.m_last_modified = contents_node->value();
                } else if (name == kGetBucketContentsETag) {
                    cnt.m_etag = contents_node->value();
                } else if (name == kGetBucketContentsSize) {
                    cnt.m_size = contents_node->value();
                } else if (name == kGetBucketContentsStorageClass) {
                    cnt.m_storage_class = contents_node->value();
                } else if (name == kGetBucketContentsOwner) {
                    rapidxml::xml_node<>* id_node = contents_node->first_node();
                    for (; id_node != NULL; id_node = id_node->next_sibling()) {
                        if (id_node->name() != kGetBucketContentsOwnerID) {
                            continue;
                        }
                        cnt.m_owner_ids.push_back(id_node->value());
                    }
                } else {
                    SDK_LOG_WARN("Unknown field in content node, field_name=%s, xml_body=%s",
                                name.c_str(), body.c_str());
                }
            }
            m_contents.push_back(cnt);
        } else {
            SDK_LOG_WARN("Unknown field, field_name=%s, xml_body=%s",
                         node_name.c_str(), body.c_str());
        }
    }
    return true;
}

bool GetBucketReplicationResp::ParseFromXmlString(const std::string& body) {
    rapidxml::xml_document<> doc;
    if (!StringUtil::StringToXml(body, &doc)) {
        SDK_LOG_ERR("Parse string to xml doc error, xml_body=%s", body.c_str());
        return false;
    }

    rapidxml::xml_node<>* root = doc.first_node(kBucketReplicationRoot.c_str());
    if (NULL == root) {
        SDK_LOG_ERR("Miss root node=BucketReplicationRoot, xml_body=%s", body.c_str());
        return false;
    }

    rapidxml::xml_node<>* node = root->first_node();
    for (; node != NULL; node = node->next_sibling()) {
        const std::string& node_name = node->name();
        if (node_name == kBucketReplicationRole) {
            m_role = node->value();
        } else if (node_name == kBucketReplicationRule) {
            rapidxml::xml_node<>* rule_node = node->first_node();
            ReplicationRule rule;
            for (; rule_node != NULL; rule_node = rule_node->next_sibling()) {
                const std::string& rule_node_name = rule_node->name();
                if (rule_node->first_node() && rule_node->first_node()->type() == rapidxml::node_data) {
                    if (rule_node_name == kBucketReplicationStatus) {
                        rule.m_is_enable = (rule_node->value() == std::string("Enabled")) ? true : false;
                    } else if (rule_node_name == kBucketReplicationID) {
                        rule.m_id = rule_node->value();
                    } else if (rule_node_name == kBucketReplicationPrefix) {
                        rule.m_prefix = rule_node->value();
                    } else {
                        SDK_LOG_WARN("Unknown field in rule node, field_name=[%s]",
                                     rule_node_name.c_str());
                    }
                } else if (rule_node_name == kBucketReplicationDestination) {
                    rapidxml::xml_node<>* dest_node = rule_node->first_node();
                    for (; dest_node != NULL; dest_node = dest_node->next_sibling()) {
                        const std::string dest_node_name = dest_node->name();
                        if (dest_node_name == kBucketReplicationBucket) {
                            rule.m_dest_bucket = dest_node->value();
                        } else if (dest_node_name == kBucketReplicationStorageClass) {
                            rule.m_dest_storage_class = dest_node->value();
                        } else {
                            SDK_LOG_WARN("Unknown field in destionation node, field_name=%s",
                                         dest_node_name.c_str());
                        }
                    }
                } else {
                    SDK_LOG_WARN("Unknown field in rule node, field_name=%s",
                                 rule_node_name.c_str());
                }
            }
            m_rules.push_back(rule);
        } else {
            SDK_LOG_WARN("Unknown field, field_name=%s, xml_body=%s",
                         node_name.c_str(), body.c_str());
        }
    }
    return true;
}

bool GetBucketLifecycleResp::ParseFromXmlString(const std::string& body) {
    rapidxml::xml_document<> doc;
    if (!StringUtil::StringToXml(body, &doc)) {
        SDK_LOG_ERR("Parse string to xml doc error, xml_body=%s", body.c_str());
        return false;
    }

    rapidxml::xml_node<>* root = doc.first_node("LifecycleConfiguration");
    if (NULL == root) {
        SDK_LOG_ERR("Miss root node=LifecycleConfiguration, xml_body=%s", body.c_str());
        return false;
    }

    rapidxml::xml_node<>* node = root->first_node();
    for (; node != NULL; node = node->next_sibling()) {
        const std::string& node_name = node->name();
        if ("Rule" == node_name) {
            rapidxml::xml_node<>* rule_node = node->first_node();
            LifecycleRule rule;
            for (; rule_node != NULL; rule_node = rule_node->next_sibling()) {
                const std::string& rule_node_name = rule_node->name();
                if ("ID" == rule_node_name) {
                    rule.SetId(rule_node->value());
                } else if ("Prefix" == rule_node_name) {
                    // Prefix可以直接作为Rule的子节点
                    LifecycleFilter filter = rule.GetFilter();
                    filter.SetPrefix(rule_node->value());
                    rule.SetFilter(filter);
                } else if ("Filter" == rule_node_name) {
                    rapidxml::xml_node<>* filter_node = rule_node->first_node();
                    LifecycleFilter filter = rule.GetFilter();
                    for (; filter_node != NULL; filter_node = filter_node->next_sibling()) {
                        const std::string& filter_node_name = filter_node->name();
                        if ("And" == filter_node_name) {
                            rapidxml::xml_node<>* and_node = filter_node->first_node();
                            for (; and_node != NULL; and_node = and_node->next_sibling()) {
                                const std::string& and_node_name = and_node->name();
                                if ("Prefix" == and_node_name) {
                                    filter.SetPrefix(and_node->value());
                                } else if ("Tag" == and_node_name) {
                                    rapidxml::xml_node<>* tag_node = and_node->first_node();
                                    LifecycleTag tag;
                                    for (; tag_node != NULL; tag_node = tag_node->next_sibling()) {
                                        const std::string& tag_node_name = tag_node->name();
                                        if ("Key" == tag_node_name) {
                                            tag.key = tag_node->value();
                                        } else if ("Value" == tag_node_name) {
                                            tag.value = tag_node->value();
                                        } else {
                                            SDK_LOG_WARN("Unknown field in tag node, field_name=%s",
                                                         tag_node_name.c_str());
                                        }
                                    }
                                    filter.AddTag(tag);
                                } else {
                                    SDK_LOG_WARN("Unknown field in and node, field_name=%s",
                                                 and_node_name.c_str());
                                }
                            }
                        } else if ("Prefix" == filter_node_name) {
                            filter.SetPrefix(filter_node->value());
                        } else if ("Tag" == filter_node_name) {
                            rapidxml::xml_node<>* tag_node = filter_node->first_node();
                            LifecycleTag tag;
                            for (; tag_node != NULL; tag_node = tag_node->next_sibling()) {
                                const std::string& tag_node_name = tag_node->name();
                                if ("Key" == tag_node_name) {
                                    tag.key = tag_node->value();
                                } else if ("Value" == tag_node_name) {
                                    tag.value = tag_node->value();
                                } else {
                                    SDK_LOG_WARN("Unknown field in tag node, field_name=%s",
                                                 tag_node_name.c_str());
                                }
                            }
                            filter.AddTag(tag);
                        } else {
                            SDK_LOG_WARN("Unknown field in filter node, field_name=%s",
                                         filter_node_name.c_str());
                        }
                    }
                } else if ("Status" == rule_node_name) {
                    rule.SetIsEnable(("Enabled" == rule_node->value()) ? true : false);
                } else if ("Transition" == rule_node_name) {
                    rapidxml::xml_node<>* trans_node = rule_node->first_node();
                    LifecycleTransition transition;
                    for (; trans_node != NULL; trans_node = trans_node->next_sibling()) {
                        const std::string& trans_node_name = trans_node->name();
                        if ("Days" == trans_node_name) {
                            transition.SetDays(StringUtil::StringToUint64(trans_node->value()));
                        } else if ("Date" == trans_node_name) {
                            transition.SetDate(trans_node->value());
                        } else if ("StorageClass" == trans_node_name) {
                            transition.SetStorageClass(trans_node->value());
                        } else {
                            SDK_LOG_WARN("Unknown field in transition node, field_name=%s",
                                         trans_node_name.c_str());
                        }
                    }
                    rule.SetTransition(transition);
                } else if ("Expiration" == rule_node_name) {
                    rapidxml::xml_node<>* expir_node = rule_node->first_node();
                    LifecycleExpiration expiration;
                    for (; expir_node != NULL; expir_node = expir_node->next_sibling()) {
                        const std::string& expir_node_name = expir_node->name();
                        if ("Days" == expir_node_name) {
                            expiration.SetDays(StringUtil::StringToUint64(expir_node->value()));
                        } else if ("Date" == expir_node_name) {
                            expiration.SetDate(expir_node->value());
                        } else if ("ExpiredObjectDeleteMarker" == expir_node_name) {
                            expiration.SetExpiredObjDelMarker(
                                (expir_node->value() == "true") ? true : false);
                        } else {
                            SDK_LOG_WARN("Unknown field in expiration node, field_name=%s",
                                         expir_node_name.c_str());
                        }
                    }
                    rule.SetExpiration(expiration);
                } else if ("NoncurrentVersionTransition" == rule_node_name) {
                    rapidxml::xml_node<>* trans_node = rule_node->first_node();
                    LifecycleNonCurrTransition transition;
                    for (; trans_node != NULL; trans_node = trans_node->next_sibling()) {
                        const std::string& trans_node_name = trans_node->name();
                        if ("NoncurrentDays" == trans_node_name) {
                            transition.SetDays(StringUtil::StringToUint64(trans_node->value()));
                        } else if ("StorageClass" == trans_node_name) {
                            transition.SetStorageClass(trans_node->value());
                        } else {
                            SDK_LOG_WARN("Unknown field in NoncurrentVersionTransition node,"
                                         "field_name=%s", trans_node_name.c_str());
                        }
                    }
                    rule.SetNonCurrTransition(transition);
                } else if ("NoncurrentVersionExpiration" == rule_node_name) {
                    rapidxml::xml_node<>* expir_node = rule_node->first_node();
                    LifecycleNonCurrExpiration expiration;
                    for (; expir_node != NULL; expir_node = expir_node->next_sibling()) {
                        const std::string& expir_node_name = expir_node->name();
                        if ("NoncurrentDays" == expir_node_name) {
                            expiration.SetDays(StringUtil::StringToUint64(expir_node->value()));
                        } else {
                            SDK_LOG_WARN("Unknown field in NoncurrentVersionExpiration node,"
                                         "field_name=%s", expir_node_name.c_str());
                        }
                    }
                    rule.SetNonCurrExpiration(expiration);
                } else if ("AbortIncompleteMultipartUpload" == rule_node_name) {
                    rapidxml::xml_node<>* abort_node = rule_node->first_node();
                    AbortIncompleteMultipartUpload abort;
                    for (; abort_node != NULL; abort_node = abort_node->next_sibling()) {
                        const std::string& abort_node_name = abort_node->name();
                        if ("DaysAfterInitiation" == abort_node_name) {
                            abort.m_days_after_init =
                                StringUtil::StringToUint64(abort_node->value());
                        } else {
                            SDK_LOG_WARN("Unknown field in AbortIncompleteMultipartUpload node,"
                                         "field_name=%s", abort_node_name.c_str());
                        }
                    }
                    rule.SetAbortIncompleteMultiUpload(abort);
                } else {
                    SDK_LOG_WARN("Unknown field in Rule node, field_name=%s",
                                 rule_node_name.c_str());
                }
                m_rules.push_back(rule);
            }
        } else {
            SDK_LOG_WARN("Unknown field in LifecycleConfiguration node, field_name=%s",
                         node_name.c_str());
        }
    }

    return true;
}

bool GetBucketACLResp::ParseFromXmlString(const std::string& body) {
    return ParseFromACLXMLString(body, &m_owner_id, &m_owner_display_name, &m_acl);
}

bool GetBucketCORSResp::ParseFromXmlString(const std::string& body) {
    rapidxml::xml_document<> doc;
    if (!StringUtil::StringToXml(body, &doc)) {
        SDK_LOG_ERR("Parse string to xml doc error, xml_body=%s", body.c_str());
        return false;
    }

    rapidxml::xml_node<>* root = doc.first_node("CORSConfiguration");
    if (NULL == root) {
        SDK_LOG_ERR("Miss root node=CORSConfiguration, xml_body=%s", body.c_str());
        return false;
    }

    rapidxml::xml_node<>* node = root->first_node();
    for (; node != NULL; node = node->next_sibling()) {
        const std::string& node_name = node->name();
        if ("CORSRule" == node_name) {
            CORSRule rule;
            rapidxml::xml_node<>* rule_node = node->first_node();
            for (; rule_node != NULL; rule_node = rule_node->next_sibling()) {
                const std::string& rule_node_name = rule_node->name();
                if ("ID" == rule_node_name) {
                    rule.m_id = rule_node->value();
                } else if ("AllowedOrigin" == rule_node_name) {
                    rule.m_allowed_origins.push_back(rule_node->value());
                } else if ("AllowedMethod" == rule_node_name) {
                    rule.m_allowed_methods.push_back(rule_node->value());
                } else if ("AllowedHeader" == rule_node_name) {
                    rule.m_allowed_headers.push_back(rule_node->value());
                } else if ("MaxAgeSeconds" == rule_node_name) {
                    rule.m_max_age_secs = rule_node->value();
                } else if ("ExposeHeader" == rule_node_name) {
                    rule.m_expose_headers.push_back(rule_node->value());
                } else {
                    SDK_LOG_WARN("Unknown field in CORSRule node, field_name=%s",
                                 node_name.c_str());
                }
            }
            m_rules.push_back(rule);
        } else {
            SDK_LOG_WARN("Unknown field in CORSConfiguration node, field_name=%s",
                         node_name.c_str());
        }
    }

    return true;
}

} // namespace qcloud_cos
