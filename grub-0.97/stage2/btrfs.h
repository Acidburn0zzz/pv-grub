/* btrfs.h - an extraction from btrfs-progs-0.18/ctree.h into one file
 *
 * Copyright (C) 2007 Oracle.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 021110-1307, USA.
 */

/* include/asm-i386/types.h */

typedef __signed__ char __s8;
typedef unsigned char __u8;
typedef __signed__ short __s16;
typedef unsigned short __u16;
typedef __signed__ int __s32;
typedef unsigned int __u32;
typedef unsigned long long __u64;
typedef __signed__ long long __s64;

typedef __s8 s8;
typedef __u8 u8;
typedef __u16 u16;
typedef __u32 u32;
typedef __u64 u64;
typedef __s64 s64;

#define __bitwise

typedef u16 __bitwise __le16;
typedef u32 __bitwise __le32;
typedef u64 __bitwise __le64;

/* linux/posix_type.h */
typedef long linux_off_t;

/* linux/little_endian.h */
#define cpu_to_le64(x) ((__u64) (x))
#define le64_to_cpu(x) ((__u64) (x))
#define cpu_to_le32(x) ((__u32) (x))
#define le32_to_cpu(x) ((__u32) (x))
#define cpu_to_le16(x) ((__u16) (x))
#define le16_to_cpu(x) ((__u16) (x))
#define le8_to_cpu(x) ((__u8) (x))
#define cpu_to_le8(x) ((__u8) (x))

/* linux/stat.h */
#define S_IFMT  00170000
#define S_IFLNK  0120000
#define S_IFREG  0100000
#define S_IFDIR  0040000
#define S_ISLNK(m)     (((m) & S_IFMT) == S_IFLNK)
#define S_ISREG(m)      (((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m)      (((m) & S_IFMT) == S_IFDIR)

struct btrfs_root;
#define BTRFS_MAGIC "_BHRfS_M"

#define BTRFS_SUPER_INFO_OFFSET (64 * 1024)
#define BTRFS_SUPER_INFO_SIZE 4096

#define BTRFS_SUPER_MIRROR_MAX  3
#define BTRFS_SUPER_MIRROR_SHIFT 12

#define PATH_MAX                1024   /* include/linux/limits.h */
#define MAX_LINK_COUNT             5   /* number of symbolic links
                                          to follow */
#define BTRFS_MAX_LEVEL 8
#define BTRFS_ROOT_TREE_OBJECTID 1ULL
#define BTRFS_EXTENT_TREE_OBJECTID 2ULL
#define BTRFS_CHUNK_TREE_OBJECTID 3ULL
#define BTRFS_DEV_TREE_OBJECTID 4ULL
#define BTRFS_FS_TREE_OBJECTID 5ULL
#define BTRFS_ROOT_TREE_DIR_OBJECTID 6ULL
#define BTRFS_CSUM_TREE_OBJECTID 7ULL

#define BTRFS_ORPHAN_OBJECTID -5ULL
#define BTRFS_TREE_LOG_OBJECTID -6ULL
#define BTRFS_TREE_LOG_FIXUP_OBJECTID -7ULL
#define BTRFS_TREE_RELOC_OBJECTID -8ULL
#define BTRFS_DATA_RELOC_TREE_OBJECTID -9ULL
#define BTRFS_EXTENT_CSUM_OBJECTID -10ULL

#define BTRFS_MULTIPLE_OBJECTIDS -255ULL
#define BTRFS_FIRST_FREE_OBJECTID 256ULL
#define BTRFS_LAST_FREE_OBJECTID -256ULL
#define BTRFS_FIRST_CHUNK_TREE_OBJECTID 256ULL
#define BTRFS_DEV_ITEMS_OBJECTID 1ULL


#define BTRFS_NAME_LEN 255
#define BTRFS_CSUM_SIZE 32
#define BTRFS_CSUM_TYPE_CRC32  0

static int btrfs_csum_sizes[] = { 4, 0 };

/* four bytes for CRC32 */
#define BTRFS_CRC32_SIZE 4
#define BTRFS_EMPTY_DIR_SIZE 0

#define BTRFS_FT_UNKNOWN       0
#define BTRFS_FT_REG_FILE      1
#define BTRFS_FT_DIR           2
#define BTRFS_FT_CHRDEV                3
#define BTRFS_FT_BLKDEV                4
#define BTRFS_FT_FIFO          5
#define BTRFS_FT_SOCK          6
#define BTRFS_FT_SYMLINK       7
#define BTRFS_FT_XATTR         8
#define BTRFS_FT_MAX           9

#define BTRFS_UUID_SIZE 16

#define BTRFS_DEFAULT_NUM_DEVICES     1
#define BTRFS_DEFAULT_NODE_SIZE       4096
#define BTRFS_DEFAULT_LEAF_SIZE       4096
#define BTRFS_NUM_CACHED_DEVICES      128

#define WARN_ON(c)
#define cassert(cond) ({ switch (-1) { case (cond): case 0: break; } })
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define offsetof(type, memb) \
       ((unsigned long)(&((type *)0)->memb))

struct btrfs_disk_key {
       __le64 objectid;
       u8 type;
       __le64 offset;
} __attribute__ ((__packed__));

/* cpu key */
struct btrfs_key {
       u64 objectid;
       u8 type;
       u64 offset;
} __attribute__ ((__packed__));

/* this represents a divice in a chunk tree */
struct btrfs_dev_item {
       __le64 devid; /* internal device id */
       __le64 total_bytes; /* size of the device */
       __le64 bytes_used;
       __le32 io_align; /* optimal io alignment */
       __le32 io_width; /* optimal io width */
       __le32 sector_size; /* minimal io size */
       __le64 type; /* type and info about this device */
       __le64 generation; /* expected generation */
        __le64 start_offset; /* of the partition on a device */

       /* info for allocation decisions */
       __le32 dev_group;

        u8 seek_speed; /* 0-100 (100 is fastest) */
       u8 bandwidth;  /* 0-100 (100 is fastest) */

        u8 uuid[BTRFS_UUID_SIZE]; /* dev uuid generated by btrfs */
       u8 fsid[BTRFS_UUID_SIZE]; /* uuid of the host FS */
} __attribute__ ((__packed__));

struct btrfs_stripe {
       __le64 devid;
       __le64 offset;
       u8 dev_uuid[BTRFS_UUID_SIZE];
} __attribute__ ((__packed__));

struct btrfs_chunk {
       /* size of this chunk in bytes */
       __le64 length;
       __le64 owner; /* objectid of the root referincing this chunk */
       __le64 stripe_len;
       __le64 type;
       __le32 io_align; /* optimal io alignment for this chunk */
       __le32 io_width; /* optimal io width for this chunk */
       __le32 sector_size; /* minimal io size for this chunk */
       __le16 num_stripes;
       __le16 sub_stripes; /* sub stripes (for raid10) */
       struct btrfs_stripe stripe;
} __attribute__ ((__packed__));

static inline unsigned long btrfs_chunk_item_size(int num_stripes)
{
       return sizeof(struct btrfs_chunk) +
               sizeof(struct btrfs_stripe) * (num_stripes - 1);
}

#define BTRFS_FSID_SIZE 16
#define BTRFS_HEADER_FLAG_WRITTEN (1 << 0)

struct btrfs_header {
       /* these first four must match the super block */
       u8 csum[BTRFS_CSUM_SIZE];
       u8 fsid[BTRFS_FSID_SIZE]; /* uuid of the host fs */
       __le64 bytenr; /* which block this node is supposed to live in */
       __le64 flags;

       /* allowed to be different from the super from here on down */
       u8 chunk_tree_uuid[BTRFS_UUID_SIZE];
       __le64 generation;
       __le64 owner;
       __le32 nritems;
       u8 level;
} __attribute__ ((__packed__));

#define BTRFS_NODEPTRS_PER_BLOCK(r) (((r)->nodesize - \
                               sizeof(struct btrfs_header)) / \
                               sizeof(struct btrfs_key_ptr))
#define __BTRFS_LEAF_DATA_SIZE(bs) ((bs) - sizeof(struct btrfs_header))
#define BTRFS_LEAF_DATA_SIZE(r) (__BTRFS_LEAF_DATA_SIZE(r->leafsize))
#define BTRFS_MAX_INLINE_DATA_SIZE(r) (BTRFS_LEAF_DATA_SIZE(r) - \
                                       sizeof(struct btrfs_item) - \
                                       sizeof(struct btrfs_file_extent_item))

#define BTRFS_SUPER_FLAG_SEEDING       (1ULL << 32)
#define BTRFS_SUPER_FLAG_METADUMP      (1ULL << 33)

/*
 * a portion of superblock which is used
 * for chunk translation (up to 14 chunks
 * with 3 stripes each.
 */
#define BTRFS_SYSTEM_CHUNK_ARRAY_SIZE 2048
#define BTRFS_LABEL_SIZE 256

/*
 * the super block basically lists the main trees of the FS
 * it currently lacks any block count etc etc
 */

struct btrfs_super_block {
       u8 csum[BTRFS_CSUM_SIZE];
       /* the first 3 fields must match struct btrfs_header */
       u8 fsid[BTRFS_FSID_SIZE];    /* FS specific uuid */
       __le64 bytenr; /* this block number */
       __le64 flags;

       /* allowed to be different from the btrfs_header from here own down */
       __le64 magic;
       __le64 generation;
       __le64 root;        /* tree root */
       __le64 chunk_root;
       __le64 log_root;

       /* this will help find the new super based on the log root */
       __le64 log_root_transid;
       __le64 total_bytes;
       __le64 bytes_used;
       __le64 root_dir_objectid;
       __le64 num_devices;
       __le32 sectorsize;
       __le32 nodesize;
       __le32 leafsize;
       __le32 stripesize;
       __le32 sys_chunk_array_size;
       __le64 chunk_root_generation;
       __le64 compat_flags;
       __le64 compat_ro_flags;
       __le64 incompat_flags;
       __le16 csum_type;
       u8 root_level;
       u8 chunk_root_level;
       u8 log_root_level;
       struct btrfs_dev_item dev_item;

       char label[BTRFS_LABEL_SIZE];

       /* future expansion */
       __le64 reserved[32];
       u8 sys_chunk_array[BTRFS_SYSTEM_CHUNK_ARRAY_SIZE];
} __attribute__ ((__packed__));

/*
 * Compat flags that we support.  If any incompat flags are set other than the
 * ones specified below then we will fail to mount
 */
#define BTRFS_FEATURE_COMPAT_SUPP      0x0
#define BTRFS_FEATURE_COMPAT_RO_SUPP   0x0
#define BTRFS_FEATURE_INCOMPAT_SUPP    0x0

/* Item header for per-leaf lookup */
struct btrfs_item {
       struct btrfs_disk_key key;
       __le32 offset;
       __le32 size;
} __attribute__ ((__packed__));

/*
 * Format of the leaves:
 * [item0, item1....itemN] [free space] [dataN...data1, data0]
 */
struct btrfs_leaf {
       struct btrfs_header header;
       struct btrfs_item items[];
} __attribute__ ((__packed__));

/*
 * keys-pointers pairs for per-node (non-leaf) lookup
 */
struct btrfs_key_ptr {
       struct btrfs_disk_key key;
       __le64 blockptr;
       __le64 generation;
} __attribute__ ((__packed__));

struct btrfs_node {
       struct btrfs_header header;
       struct btrfs_key_ptr ptrs[];
} __attribute__ ((__packed__));

struct btrfs_device {
	/* the internal btrfs device id */
	u64 devid;
	/* the internal grub device representation */
	unsigned long drive;
	unsigned long part;
	unsigned long length;
};

struct extent_buffer {
       /* metadata */
       struct btrfs_device dev;
       u64 start;
       u64 dev_bytenr;
       u32 len;
       /* data */
       char *data;
};

static inline void read_extent_buffer(struct extent_buffer *eb,
                                     void *dst, unsigned long start,
                                     unsigned long len)
{
       memcpy(dst, eb->data + start, len);
}

static inline void write_extent_buffer(struct extent_buffer *eb,
                                      const void *src, unsigned long start,
                                      unsigned long len)
{
       memcpy(eb->data + start, src, len);
}

/*
 * NOTE:
 * don't increase a number of levels for grub-0.97!
 */
typedef enum {
       FIRST_EXTERNAL_LOOKUP_POOL,
       SECOND_EXTERNAL_LOOKUP_POOL,
       INTERNAL_LOOKUP_POOL,
       LAST_LOOKUP_POOL
} lookup_pool_id;

/*             Relationship between lookup pools:
 *  depth
 *
 *    ^             +----> INTERNAL <----+
 *    |             |                    |
 *    |             |                    |
 *    -        FIRST_EXTERNAL     SECOND_EXTERNAL
 */

struct btrfs_path {
       lookup_pool_id lpid;
       struct extent_buffer nodes[BTRFS_MAX_LEVEL];
       int slots[BTRFS_MAX_LEVEL];
};

/*
 * items in the extent btree are used to record the objectid of the
 * owner of the block and the number of references
 */
struct btrfs_extent_item {
       __le32 refs;
} __attribute__ ((__packed__));

struct btrfs_extent_ref {
       __le64 root;
       __le64 generation;
       __le64 objectid;
       __le32 num_refs;
} __attribute__ ((__packed__));

/* dev extents record free space on individual devices.  The owner
 * field points back to the chunk allocation mapping tree that allocated
 * the extent.  The chunk tree uuid field is a way to double check the owner
 */
struct btrfs_dev_extent {
       __le64 chunk_tree;
       __le64 chunk_objectid;
       __le64 chunk_offset;
       __le64 length;
       u8 chunk_tree_uuid[BTRFS_UUID_SIZE];
} __attribute__ ((__packed__));

struct btrfs_inode_ref {
       __le64 index;
       __le16 name_len;
       /* name goes here */
} __attribute__ ((__packed__));

struct btrfs_timespec {
       __le64 sec;
       __le32 nsec;
} __attribute__ ((__packed__));

typedef enum {
       BTRFS_COMPRESS_NONE = 0,
       BTRFS_COMPRESS_ZLIB = 1,
       BTRFS_COMPRESS_LAST = 2,
} btrfs_compression_type;

/* we don't understand any encryption methods right now */
typedef enum {
       BTRFS_ENCRYPTION_NONE = 0,
       BTRFS_ENCRYPTION_LAST = 1,
} btrfs_encryption_type;

struct btrfs_inode_item {
       /* nfs style generation number */
       __le64 generation;
       /* transid that last touched this inode */
       __le64 transid;
       __le64 size;
       __le64 nbytes;
       __le64 block_group;
       __le32 nlink;
       __le32 uid;
       __le32 gid;
       __le32 mode;
       __le64 rdev;
       __le64 flags;

       /* modification sequence number for NFS */
       __le64 sequence;

       /*
        * a little future expansion, for more than this we can
        * just grow the inode item and version it
        */
       __le64 reserved[4];
       struct btrfs_timespec atime;
       struct btrfs_timespec ctime;
       struct btrfs_timespec mtime;
       struct btrfs_timespec otime;
} __attribute__ ((__packed__));

struct btrfs_dir_item {
       struct btrfs_disk_key location;
       __le64 transid;
       __le16 data_len;
       __le16 name_len;
       u8 type;
} __attribute__ ((__packed__));

struct btrfs_root_item {
       struct btrfs_inode_item inode;
       __le64 generation;
       __le64 root_dirid;
       __le64 bytenr;
       __le64 byte_limit;
       __le64 bytes_used;
       __le64 last_snapshot;
       __le64 flags;
       __le32 refs;
       struct btrfs_disk_key drop_progress;
       u8 drop_level;
       u8 level;
} __attribute__ ((__packed__));

/*
 * this is used for both forward and backward root refs
 */
struct btrfs_root_ref {
       __le64 dirid;
       __le64 sequence;
       __le16 name_len;
} __attribute__ ((__packed__));

#define BTRFS_FILE_EXTENT_INLINE 0
#define BTRFS_FILE_EXTENT_REG 1
#define BTRFS_FILE_EXTENT_PREALLOC 2

struct btrfs_file_extent_item {
       /*
        * transaction id that created this extent
        */
       __le64 generation;
       /*
        * max number of bytes to hold this extent in ram
        * when we split a compressed extent we can't know how big
        * each of the resulting pieces will be.  So, this is
        * an upper limit on the size of the extent in ram instead of
        * an exact limit.
        */
       __le64 ram_bytes;

       /*
        * 32 bits for the various ways we might encode the data,
        * including compression and encryption.  If any of these
        * are set to something a given disk format doesn't understand
        * it is treated like an incompat flag for reading and writing,
        * but not for stat.
        */
       u8 compression;
       u8 encryption;
       __le16 other_encoding; /* spare for later use */

       /* are we inline data or a real extent? */
       u8 type;

       /*
        * disk space consumed by the extent, checksum blocks are included
        * in these numbers
        */
       __le64 disk_bytenr;
       __le64 disk_num_bytes;
       /*
        * the logical offset in file blocks (no csums)
        * this extent record is for.  This allows a file extent to point
        * into the middle of an existing extent on disk, sharing it
        * between two snapshots (useful if some bytes in the middle of the
        * extent have changed
        */
       __le64 offset;
       /*
        * the logical number of file blocks (no csums included)
        */
       __le64 num_bytes;

} __attribute__ ((__packed__));

struct btrfs_csum_item {
       u8 csum;
} __attribute__ ((__packed__));

/* tag for the radix tree of block groups in ram */
#define BTRFS_BLOCK_GROUP_DATA     (1 << 0)
#define BTRFS_BLOCK_GROUP_SYSTEM   (1 << 1)
#define BTRFS_BLOCK_GROUP_METADATA (1 << 2)
#define BTRFS_BLOCK_GROUP_RAID0    (1 << 3)
#define BTRFS_BLOCK_GROUP_RAID1    (1 << 4)
#define BTRFS_BLOCK_GROUP_DUP     (1 << 5)
#define BTRFS_BLOCK_GROUP_RAID10   (1 << 6)

struct btrfs_block_group_item {
       __le64 used;
       __le64 chunk_objectid;
       __le64 flags;
} __attribute__ ((__packed__));

/*
 * in ram representation of the tree.  extent_root is used for all allocations
 * and for the extent tree extent_root root.
 */
struct btrfs_root {
       struct extent_buffer   node;
       char                   data[4096];
       struct btrfs_root_item root_item;
       u64 objectid;
       
       /* data allocations are done in sectorsize units */
       u32 sectorsize;

       /* node allocations are done in nodesize units */
       u32 nodesize;

       /* leaf allocations are done in leafsize units */
       u32 leafsize;

       /* leaf allocations are done in leafsize units */
       u32 stripesize;
};

struct btrfs_file_info {
	struct btrfs_key key;
};

struct btrfs_root;
struct btrfs_fs_devices;
struct btrfs_fs_info {
       u8 fsid[BTRFS_FSID_SIZE];
       struct btrfs_root fs_root;
       struct btrfs_root tree_root;
       struct btrfs_root chunk_root;

       struct btrfs_file_info file_info; /* currently opened file */
       struct btrfs_path paths [LAST_LOOKUP_POOL];

       char mbr[SECTOR_SIZE];

       int sb_mirror;
       u64 sb_transid;
       struct btrfs_device sb_dev;
       struct btrfs_super_block sb_copy;

       struct btrfs_device devices[BTRFS_NUM_CACHED_DEVICES + 1];
};

/*
 * inode items have the data typically returned from stat and store other
 * info about object characteristics.  There is one for every file and dir in
 * the FS
 */
#define BTRFS_INODE_ITEM_KEY           1
#define BTRFS_INODE_REF_KEY            12
#define BTRFS_XATTR_ITEM_KEY           24
#define BTRFS_ORPHAN_ITEM_KEY          48

#define BTRFS_DIR_LOG_ITEM_KEY  60
#define BTRFS_DIR_LOG_INDEX_KEY 72
/*
 * dir items are the name -> inode pointers in a directory.  There is one
 * for every name in a directory.
 */
#define BTRFS_DIR_ITEM_KEY     84
#define BTRFS_DIR_INDEX_KEY    96

/*
 * extent data is for file data
 */
#define BTRFS_EXTENT_DATA_KEY  108

/*
 * csum items have the checksums for data in the extents
 */
#define BTRFS_CSUM_ITEM_KEY    120
/*
 * extent csums are stored in a separate tree and hold csums for
 * an entire extent on disk.
 */
#define BTRFS_EXTENT_CSUM_KEY  128

/*
 * root items point to tree roots.  There are typically in the root
 * tree used by the super block to find all the other trees
 */
#define BTRFS_ROOT_ITEM_KEY    132

/*
 * root backrefs tie subvols and snapshots to the directory entries that
 * reference them
 */
#define BTRFS_ROOT_BACKREF_KEY 144

/*
 * root refs make a fast index for listing all of the snapshots and
 * subvolumes referenced by a given root.  They point directly to the
 * directory item in the root that references the subvol
 */
#define BTRFS_ROOT_REF_KEY     156

/*
+ * extent items are in the extent map tree.  These record which blocks
+ * are used, and how many references there are to each block
+ */
#define BTRFS_EXTENT_ITEM_KEY  168
#define BTRFS_EXTENT_REF_KEY   180

/*
 * block groups give us hints into the extent allocation trees.  Which
 * blocks are free etc etc
 */
#define BTRFS_BLOCK_GROUP_ITEM_KEY 192

#define BTRFS_DEV_EXTENT_KEY   204
#define BTRFS_DEV_ITEM_KEY     216
#define BTRFS_CHUNK_ITEM_KEY   228

/*
 * string items are for debugging.  They just store a short string of
 * data in the FS
 */
#define BTRFS_STRING_ITEM_KEY  253
/*
 * Inode flags
 */
#define BTRFS_INODE_NODATASUM          (1 << 0)
#define BTRFS_INODE_NODATACOW          (1 << 1)
#define BTRFS_INODE_READONLY           (1 << 2)

#define read_eb_member(eb, ptr, type, member, result) (                        \
       read_extent_buffer(eb, (char *)(result),                        \
                          ((unsigned long)(ptr)) +                     \
                           offsetof(type, member),                     \
                          sizeof(((type *)0)->member)))

#define BTRFS_SETGET_HEADER_FUNCS(name, type, member, bits)            \
static inline u##bits btrfs_##name(struct extent_buffer *eb)           \
{                                                                      \
       struct btrfs_header *h = (struct btrfs_header *)eb->data;       \
       return le##bits##_to_cpu(h->member);                            \
}                                                                      \
static inline void btrfs_set_##name(struct extent_buffer *eb,          \
                                   u##bits val)                        \
{                                                                      \
       struct btrfs_header *h = (struct btrfs_header *)eb->data;       \
       h->member = cpu_to_le##bits(val);                               \
}

#define BTRFS_SETGET_FUNCS(name, type, member, bits)                   \
static inline u##bits btrfs_##name(struct extent_buffer *eb,           \
                                  type *s)                             \
{                                                                      \
       unsigned long offset = (unsigned long)s;                        \
       type *p = (type *) (eb->data + offset);                         \
       return le##bits##_to_cpu(p->member);                            \
}                                                                      \
static inline void btrfs_set_##name(struct extent_buffer *eb,          \
                                   type *s, u##bits val)               \
{                                                                      \
       unsigned long offset = (unsigned long)s;                        \
       type *p = (type *) (eb->data + offset);                         \
       p->member = cpu_to_le##bits(val);                               \
}

#define BTRFS_SETGET_STACK_FUNCS(name, type, member, bits)             \
static inline u##bits btrfs_##name(type *s)                            \
{                                                                      \
       return le##bits##_to_cpu(s->member);                            \
}                                                                      \
static inline void btrfs_set_##name(type *s, u##bits val)              \
{                                                                      \
       s->member = cpu_to_le##bits(val);                               \
}

BTRFS_SETGET_FUNCS(device_type, struct btrfs_dev_item, type, 64);
BTRFS_SETGET_FUNCS(device_total_bytes, struct btrfs_dev_item, total_bytes, 64);
BTRFS_SETGET_FUNCS(device_bytes_used, struct btrfs_dev_item, bytes_used, 64);
BTRFS_SETGET_FUNCS(device_io_align, struct btrfs_dev_item, io_align, 32);
BTRFS_SETGET_FUNCS(device_io_width, struct btrfs_dev_item, io_width, 32);
BTRFS_SETGET_FUNCS(device_start_offset, struct btrfs_dev_item,
                  start_offset, 64);
BTRFS_SETGET_FUNCS(device_sector_size, struct btrfs_dev_item, sector_size, 32);
BTRFS_SETGET_FUNCS(device_id, struct btrfs_dev_item, devid, 64);
BTRFS_SETGET_FUNCS(device_group, struct btrfs_dev_item, dev_group, 32);
BTRFS_SETGET_FUNCS(device_seek_speed, struct btrfs_dev_item, seek_speed, 8);
BTRFS_SETGET_FUNCS(device_bandwidth, struct btrfs_dev_item, bandwidth, 8);
BTRFS_SETGET_FUNCS(device_generation, struct btrfs_dev_item, generation, 64);

BTRFS_SETGET_STACK_FUNCS(stack_device_type, struct btrfs_dev_item, type, 64);
BTRFS_SETGET_STACK_FUNCS(stack_device_total_bytes, struct btrfs_dev_item,
                        total_bytes, 64);
BTRFS_SETGET_STACK_FUNCS(stack_device_bytes_used, struct btrfs_dev_item,
                        bytes_used, 64);
BTRFS_SETGET_STACK_FUNCS(stack_device_io_align, struct btrfs_dev_item,
                        io_align, 32);
BTRFS_SETGET_STACK_FUNCS(stack_device_io_width, struct btrfs_dev_item,
                        io_width, 32);
BTRFS_SETGET_STACK_FUNCS(stack_device_sector_size, struct btrfs_dev_item,
                        sector_size, 32);
BTRFS_SETGET_STACK_FUNCS(stack_device_id, struct btrfs_dev_item, devid, 64);
BTRFS_SETGET_STACK_FUNCS(stack_device_group, struct btrfs_dev_item,
                        dev_group, 32);
BTRFS_SETGET_STACK_FUNCS(stack_device_seek_speed, struct btrfs_dev_item,
                        seek_speed, 8);
BTRFS_SETGET_STACK_FUNCS(stack_device_bandwidth, struct btrfs_dev_item,
                        bandwidth, 8);
BTRFS_SETGET_STACK_FUNCS(stack_device_generation, struct btrfs_dev_item,
                        generation, 64);

static inline char *btrfs_device_uuid(struct btrfs_dev_item *d)
{
       return (char *)d + offsetof(struct btrfs_dev_item, uuid);
}

static inline char *btrfs_device_fsid(struct btrfs_dev_item *d)
{
       return (char *)d + offsetof(struct btrfs_dev_item, fsid);
}

BTRFS_SETGET_FUNCS(chunk_length, struct btrfs_chunk, length, 64);
BTRFS_SETGET_FUNCS(chunk_owner, struct btrfs_chunk, owner, 64);
BTRFS_SETGET_FUNCS(chunk_stripe_len, struct btrfs_chunk, stripe_len, 64);
BTRFS_SETGET_FUNCS(chunk_io_align, struct btrfs_chunk, io_align, 32);
BTRFS_SETGET_FUNCS(chunk_io_width, struct btrfs_chunk, io_width, 32);
BTRFS_SETGET_FUNCS(chunk_sector_size, struct btrfs_chunk, sector_size, 32);
BTRFS_SETGET_FUNCS(chunk_type, struct btrfs_chunk, type, 64);
BTRFS_SETGET_FUNCS(chunk_num_stripes, struct btrfs_chunk, num_stripes, 16);
BTRFS_SETGET_FUNCS(chunk_sub_stripes, struct btrfs_chunk, sub_stripes, 16);
BTRFS_SETGET_FUNCS(stripe_devid, struct btrfs_stripe, devid, 64);
BTRFS_SETGET_FUNCS(stripe_offset, struct btrfs_stripe, offset, 64);

static inline char *btrfs_stripe_dev_uuid(struct btrfs_stripe *s)
{
       return (char *)s + offsetof(struct btrfs_stripe, dev_uuid);
}

BTRFS_SETGET_STACK_FUNCS(stack_chunk_length, struct btrfs_chunk, length, 64);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_owner, struct btrfs_chunk, owner, 64);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_stripe_len, struct btrfs_chunk,
                        stripe_len, 64);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_io_align, struct btrfs_chunk,
                        io_align, 32);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_io_width, struct btrfs_chunk,
                        io_width, 32);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_sector_size, struct btrfs_chunk,
                        sector_size, 32);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_type, struct btrfs_chunk, type, 64);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_num_stripes, struct btrfs_chunk,
                        num_stripes, 16);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_sub_stripes, struct btrfs_chunk,
                        sub_stripes, 16);
BTRFS_SETGET_STACK_FUNCS(stack_stripe_devid, struct btrfs_stripe, devid, 64);
BTRFS_SETGET_STACK_FUNCS(stack_stripe_offset, struct btrfs_stripe, offset, 64);

static inline struct btrfs_stripe *btrfs_stripe_nr(struct btrfs_chunk *c,
                                                  int nr)
{
       unsigned long offset = (unsigned long)c;
       offset += offsetof(struct btrfs_chunk, stripe);
       offset += nr * sizeof(struct btrfs_stripe);
       return (struct btrfs_stripe *)offset;
}

static inline char *btrfs_stripe_dev_uuid_nr(struct btrfs_chunk *c, int nr)
{
       return btrfs_stripe_dev_uuid(btrfs_stripe_nr(c, nr));
}

static inline u64 btrfs_stripe_offset_nr(struct extent_buffer *eb,
                                        struct btrfs_chunk *c, int nr)
{
       return btrfs_stripe_offset(eb, btrfs_stripe_nr(c, nr));
}

static inline void btrfs_set_stripe_offset_nr(struct extent_buffer *eb,
                                            struct btrfs_chunk *c, int nr,
                                            u64 val)
{
       btrfs_set_stripe_offset(eb, btrfs_stripe_nr(c, nr), val);
}

static inline u64 btrfs_stripe_devid_nr(struct extent_buffer *eb,
                                        struct btrfs_chunk *c, int nr)
{
       return btrfs_stripe_devid(eb, btrfs_stripe_nr(c, nr));
}

static inline void btrfs_set_stripe_devid_nr(struct extent_buffer *eb,
                                            struct btrfs_chunk *c, int nr,
                                            u64 val)
{
       btrfs_set_stripe_devid(eb, btrfs_stripe_nr(c, nr), val);
}

/* struct btrfs_block_group_item */
BTRFS_SETGET_STACK_FUNCS(block_group_used, struct btrfs_block_group_item,
                        used, 64);
BTRFS_SETGET_FUNCS(disk_block_group_used, struct btrfs_block_group_item,
                        used, 64);
BTRFS_SETGET_STACK_FUNCS(block_group_chunk_objectid,
                       struct btrfs_block_group_item, chunk_objectid, 64);

BTRFS_SETGET_FUNCS(disk_block_group_chunk_objectid,
                  struct btrfs_block_group_item, chunk_objectid, 64);
BTRFS_SETGET_FUNCS(disk_block_group_flags,
                  struct btrfs_block_group_item, flags, 64);
BTRFS_SETGET_STACK_FUNCS(block_group_flags,
                       struct btrfs_block_group_item, flags, 64);

/* struct btrfs_inode_ref */
BTRFS_SETGET_FUNCS(inode_ref_name_len, struct btrfs_inode_ref, name_len, 16);
BTRFS_SETGET_FUNCS(inode_ref_index, struct btrfs_inode_ref, index, 64);

/* struct btrfs_inode_item */
BTRFS_SETGET_FUNCS(inode_generation, struct btrfs_inode_item, generation, 64);
BTRFS_SETGET_FUNCS(inode_sequence, struct btrfs_inode_item, sequence, 64);
BTRFS_SETGET_FUNCS(inode_transid, struct btrfs_inode_item, transid, 64);
BTRFS_SETGET_FUNCS(inode_size, struct btrfs_inode_item, size, 64);
BTRFS_SETGET_FUNCS(inode_nbytes, struct btrfs_inode_item, nbytes, 64);
BTRFS_SETGET_FUNCS(inode_block_group, struct btrfs_inode_item, block_group, 64);
BTRFS_SETGET_FUNCS(inode_nlink, struct btrfs_inode_item, nlink, 32);
BTRFS_SETGET_FUNCS(inode_uid, struct btrfs_inode_item, uid, 32);
BTRFS_SETGET_FUNCS(inode_gid, struct btrfs_inode_item, gid, 32);
BTRFS_SETGET_FUNCS(inode_mode, struct btrfs_inode_item, mode, 32);
BTRFS_SETGET_FUNCS(inode_rdev, struct btrfs_inode_item, rdev, 64);
BTRFS_SETGET_FUNCS(inode_flags, struct btrfs_inode_item, flags, 64);

BTRFS_SETGET_STACK_FUNCS(stack_inode_generation,
                        struct btrfs_inode_item, generation, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_sequence,
                        struct btrfs_inode_item, generation, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_size,
                        struct btrfs_inode_item, size, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_nbytes,
                        struct btrfs_inode_item, nbytes, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_block_group,
                        struct btrfs_inode_item, block_group, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_nlink,
                        struct btrfs_inode_item, nlink, 32);
BTRFS_SETGET_STACK_FUNCS(stack_inode_uid,
                        struct btrfs_inode_item, uid, 32);
BTRFS_SETGET_STACK_FUNCS(stack_inode_gid,
                        struct btrfs_inode_item, gid, 32);
BTRFS_SETGET_STACK_FUNCS(stack_inode_mode,
                        struct btrfs_inode_item, mode, 32);
BTRFS_SETGET_STACK_FUNCS(stack_inode_rdev,
                        struct btrfs_inode_item, rdev, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_flags,
                        struct btrfs_inode_item, flags, 64);

BTRFS_SETGET_FUNCS(timespec_sec, struct btrfs_timespec, sec, 64);
BTRFS_SETGET_FUNCS(timespec_nsec, struct btrfs_timespec, nsec, 32);
BTRFS_SETGET_STACK_FUNCS(stack_timespec_sec, struct btrfs_timespec,
                        sec, 64);
BTRFS_SETGET_STACK_FUNCS(stack_timespec_nsec, struct btrfs_timespec,
                        nsec, 32);

/* struct btrfs_dev_extent */
BTRFS_SETGET_FUNCS(dev_extent_chunk_tree, struct btrfs_dev_extent,
                  chunk_tree, 64);
BTRFS_SETGET_FUNCS(dev_extent_chunk_objectid, struct btrfs_dev_extent,
                  chunk_objectid, 64);
BTRFS_SETGET_FUNCS(dev_extent_chunk_offset, struct btrfs_dev_extent,
                  chunk_offset, 64);
BTRFS_SETGET_FUNCS(dev_extent_length, struct btrfs_dev_extent, length, 64);

static inline u8 *btrfs_dev_extent_chunk_tree_uuid(struct btrfs_dev_extent *dev)
{
       unsigned long ptr = offsetof(struct btrfs_dev_extent, chunk_tree_uuid);
       return (u8 *)((unsigned long)dev + ptr);
}

/* struct btrfs_extent_ref */
BTRFS_SETGET_FUNCS(ref_root, struct btrfs_extent_ref, root, 64);
BTRFS_SETGET_FUNCS(ref_generation, struct btrfs_extent_ref, generation, 64);
BTRFS_SETGET_FUNCS(ref_objectid, struct btrfs_extent_ref, objectid, 64);
BTRFS_SETGET_FUNCS(ref_num_refs, struct btrfs_extent_ref, num_refs, 32);

BTRFS_SETGET_STACK_FUNCS(stack_ref_root, struct btrfs_extent_ref, root, 64);
BTRFS_SETGET_STACK_FUNCS(stack_ref_generation, struct btrfs_extent_ref,
                        generation, 64);
BTRFS_SETGET_STACK_FUNCS(stack_ref_objectid, struct btrfs_extent_ref,
                        objectid, 64);
BTRFS_SETGET_STACK_FUNCS(stack_ref_num_refs, struct btrfs_extent_ref,
                        num_refs, 32);

/* struct btrfs_extent_item */
BTRFS_SETGET_FUNCS(extent_refs, struct btrfs_extent_item, refs, 32);
BTRFS_SETGET_STACK_FUNCS(stack_extent_refs, struct btrfs_extent_item,
                        refs, 32);

/* struct btrfs_node */
BTRFS_SETGET_FUNCS(key_blockptr, struct btrfs_key_ptr, blockptr, 64);
BTRFS_SETGET_FUNCS(key_generation, struct btrfs_key_ptr, generation, 64);

static inline u64 btrfs_node_blockptr(struct extent_buffer *eb, int nr)
{
       unsigned long ptr;
       ptr = offsetof(struct btrfs_node, ptrs) +
               sizeof(struct btrfs_key_ptr) * nr;
       return btrfs_key_blockptr(eb, (struct btrfs_key_ptr *)ptr);
}

static inline void btrfs_set_node_blockptr(struct extent_buffer *eb,
                                          int nr, u64 val)
{
       unsigned long ptr;
       ptr = offsetof(struct btrfs_node, ptrs) +
               sizeof(struct btrfs_key_ptr) * nr;
       btrfs_set_key_blockptr(eb, (struct btrfs_key_ptr *)ptr, val);
}

static inline u64 btrfs_node_ptr_generation(struct extent_buffer *eb, int nr)
{
       unsigned long ptr;
       ptr = offsetof(struct btrfs_node, ptrs) +
               sizeof(struct btrfs_key_ptr) * nr;
       return btrfs_key_generation(eb, (struct btrfs_key_ptr *)ptr);
}

static inline void btrfs_set_node_ptr_generation(struct extent_buffer *eb,
                                                int nr, u64 val)
{
       unsigned long ptr;
       ptr = offsetof(struct btrfs_node, ptrs) +
               sizeof(struct btrfs_key_ptr) * nr;
       btrfs_set_key_generation(eb, (struct btrfs_key_ptr *)ptr, val);
}

static inline unsigned long btrfs_node_key_ptr_offset(int nr)
{
       return offsetof(struct btrfs_node, ptrs) +
               sizeof(struct btrfs_key_ptr) * nr;
}

static inline void btrfs_node_key(struct extent_buffer *eb,
                                 struct btrfs_disk_key *disk_key, int nr)
{
       unsigned long ptr;
       ptr = btrfs_node_key_ptr_offset(nr);
       read_eb_member(eb, (struct btrfs_key_ptr *)ptr,
                      struct btrfs_key_ptr, key, disk_key);
}

/* struct btrfs_item */
BTRFS_SETGET_FUNCS(item_offset, struct btrfs_item, offset, 32);
BTRFS_SETGET_FUNCS(item_size, struct btrfs_item, size, 32);

static inline unsigned long btrfs_item_nr_offset(int nr)
{
       return offsetof(struct btrfs_leaf, items) +
               sizeof(struct btrfs_item) * nr;
}

static inline struct btrfs_item *btrfs_item_nr(struct extent_buffer *eb,
                                              int nr)
{
       return (struct btrfs_item *)btrfs_item_nr_offset(nr);
}

static inline u32 btrfs_item_end(struct extent_buffer *eb,
                                struct btrfs_item *item)
{
       return btrfs_item_offset(eb, item) + btrfs_item_size(eb, item);
}

static inline u32 btrfs_item_end_nr(struct extent_buffer *eb, int nr)
{
       return btrfs_item_end(eb, btrfs_item_nr(eb, nr));
}

static inline u32 btrfs_item_offset_nr(struct extent_buffer *eb, int nr)
{
       return btrfs_item_offset(eb, btrfs_item_nr(eb, nr));
}

static inline u32 btrfs_item_size_nr(struct extent_buffer *eb, int nr)
{
       return btrfs_item_size(eb, btrfs_item_nr(eb, nr));
}

static inline void btrfs_item_key(struct extent_buffer *eb,
                          struct btrfs_disk_key *disk_key, int nr)
{
       struct btrfs_item *item = btrfs_item_nr(eb, nr);
       read_eb_member(eb, item, struct btrfs_item, key, disk_key);
}

/*
 * struct btrfs_root_ref
 */
BTRFS_SETGET_FUNCS(root_ref_dirid, struct btrfs_root_ref, dirid, 64);
BTRFS_SETGET_FUNCS(root_ref_sequence, struct btrfs_root_ref, sequence, 64);
BTRFS_SETGET_FUNCS(root_ref_name_len, struct btrfs_root_ref, name_len, 16);

/* struct btrfs_dir_item */
BTRFS_SETGET_FUNCS(dir_data_len, struct btrfs_dir_item, data_len, 16);
BTRFS_SETGET_FUNCS(dir_type, struct btrfs_dir_item, type, 8);
BTRFS_SETGET_FUNCS(dir_name_len, struct btrfs_dir_item, name_len, 16);
BTRFS_SETGET_FUNCS(dir_transid, struct btrfs_dir_item, transid, 64);

static inline void btrfs_dir_item_key(struct extent_buffer *eb,
                                     struct btrfs_dir_item *item,
                                     struct btrfs_disk_key *key)
{
       read_eb_member(eb, item, struct btrfs_dir_item, location, key);
}

/* struct btrfs_disk_key */
BTRFS_SETGET_STACK_FUNCS(disk_key_objectid, struct btrfs_disk_key,
                        objectid, 64);
BTRFS_SETGET_STACK_FUNCS(disk_key_offset, struct btrfs_disk_key, offset, 64);
BTRFS_SETGET_STACK_FUNCS(disk_key_type, struct btrfs_disk_key, type, 8);

static inline void btrfs_disk_key_to_cpu(struct btrfs_key *cpu,
                                        struct btrfs_disk_key *disk)
{
       cpu->offset = le64_to_cpu(disk->offset);
       cpu->type = disk->type;
       cpu->objectid = le64_to_cpu(disk->objectid);
}

static inline void btrfs_cpu_key_to_disk(struct btrfs_disk_key *disk,
                                        struct btrfs_key *cpu)
{
       disk->offset = cpu_to_le64(cpu->offset);
       disk->type = cpu->type;
       disk->objectid = cpu_to_le64(cpu->objectid);
}

static inline void btrfs_node_key_to_cpu(struct extent_buffer *eb,
                                 struct btrfs_key *key, int nr)
{
       struct btrfs_disk_key disk_key;
       btrfs_node_key(eb, &disk_key, nr);
       btrfs_disk_key_to_cpu(key, &disk_key);
}

static inline void btrfs_item_key_to_cpu(struct extent_buffer *eb,
                                 struct btrfs_key *key, int nr)
{
       struct btrfs_disk_key disk_key;
       btrfs_item_key(eb, &disk_key, nr);
       btrfs_disk_key_to_cpu(key, &disk_key);
}

static inline void btrfs_dir_item_key_to_cpu(struct extent_buffer *eb,
                                     struct btrfs_dir_item *item,
                                     struct btrfs_key *key)
{
       struct btrfs_disk_key disk_key;
       btrfs_dir_item_key(eb, item, &disk_key);
       btrfs_disk_key_to_cpu(key, &disk_key);
}

static inline u8 btrfs_key_type(struct btrfs_key *key)
{
       return key->type;
}

static inline void btrfs_set_key_type(struct btrfs_key *key, u8 val)
{
       key->type = val;
}

static inline u64 btrfs_super_devid(struct btrfs_super_block *disk_super)
{
	return le64_to_cpu(disk_super->dev_item.devid);
}

/* struct btrfs_header */
BTRFS_SETGET_HEADER_FUNCS(header_bytenr, struct btrfs_header, bytenr, 64);
BTRFS_SETGET_HEADER_FUNCS(header_generation, struct btrfs_header,
                         generation, 64);
BTRFS_SETGET_HEADER_FUNCS(header_owner, struct btrfs_header, owner, 64);
BTRFS_SETGET_HEADER_FUNCS(header_nritems, struct btrfs_header, nritems, 32);
BTRFS_SETGET_HEADER_FUNCS(header_flags, struct btrfs_header, flags, 64);
BTRFS_SETGET_HEADER_FUNCS(header_level, struct btrfs_header, level, 8);

/* struct btrfs_root_item */
BTRFS_SETGET_FUNCS(disk_root_generation, struct btrfs_root_item,
                  generation, 64);
BTRFS_SETGET_FUNCS(disk_root_refs, struct btrfs_root_item, refs, 32);
BTRFS_SETGET_FUNCS(disk_root_bytenr, struct btrfs_root_item, bytenr, 64);
BTRFS_SETGET_FUNCS(disk_root_level, struct btrfs_root_item, level, 8);

BTRFS_SETGET_STACK_FUNCS(root_generation, struct btrfs_root_item,
                        generation, 64);
BTRFS_SETGET_STACK_FUNCS(root_bytenr, struct btrfs_root_item, bytenr, 64);
BTRFS_SETGET_STACK_FUNCS(root_level, struct btrfs_root_item, level, 8);
BTRFS_SETGET_STACK_FUNCS(root_dirid, struct btrfs_root_item, root_dirid, 64);
BTRFS_SETGET_STACK_FUNCS(root_refs, struct btrfs_root_item, refs, 32);
BTRFS_SETGET_STACK_FUNCS(root_flags, struct btrfs_root_item, flags, 64);
BTRFS_SETGET_STACK_FUNCS(root_used, struct btrfs_root_item, bytes_used, 64);
BTRFS_SETGET_STACK_FUNCS(root_limit, struct btrfs_root_item, byte_limit, 64);
BTRFS_SETGET_STACK_FUNCS(root_last_snapshot, struct btrfs_root_item,
                        last_snapshot, 64);

/* struct btrfs_super_block */

BTRFS_SETGET_STACK_FUNCS(super_bytenr, struct btrfs_super_block, bytenr, 64);
BTRFS_SETGET_STACK_FUNCS(super_flags, struct btrfs_super_block, flags, 64);
BTRFS_SETGET_STACK_FUNCS(super_generation, struct btrfs_super_block,
                        generation, 64);
BTRFS_SETGET_STACK_FUNCS(super_root, struct btrfs_super_block, root, 64);
BTRFS_SETGET_STACK_FUNCS(super_sys_array_size,
                        struct btrfs_super_block, sys_chunk_array_size, 32);
BTRFS_SETGET_STACK_FUNCS(super_chunk_root_generation,
                        struct btrfs_super_block, chunk_root_generation, 64);
BTRFS_SETGET_STACK_FUNCS(super_root_level, struct btrfs_super_block,
                        root_level, 8);
BTRFS_SETGET_STACK_FUNCS(super_chunk_root, struct btrfs_super_block,
                        chunk_root, 64);
BTRFS_SETGET_STACK_FUNCS(super_chunk_root_level, struct btrfs_super_block,
                        chunk_root_level, 8);
BTRFS_SETGET_STACK_FUNCS(super_log_root, struct btrfs_super_block,
                        log_root, 64);
BTRFS_SETGET_STACK_FUNCS(super_log_root_transid, struct btrfs_super_block,
                        log_root_transid, 64);
BTRFS_SETGET_STACK_FUNCS(super_log_root_level, struct btrfs_super_block,
                        log_root_level, 8);
BTRFS_SETGET_STACK_FUNCS(super_total_bytes, struct btrfs_super_block,
                        total_bytes, 64);
BTRFS_SETGET_STACK_FUNCS(super_bytes_used, struct btrfs_super_block,
                        bytes_used, 64);
BTRFS_SETGET_STACK_FUNCS(super_sectorsize, struct btrfs_super_block,
                        sectorsize, 32);
BTRFS_SETGET_STACK_FUNCS(super_nodesize, struct btrfs_super_block,
                        nodesize, 32);
BTRFS_SETGET_STACK_FUNCS(super_leafsize, struct btrfs_super_block,
                        leafsize, 32);
BTRFS_SETGET_STACK_FUNCS(super_stripesize, struct btrfs_super_block,
                        stripesize, 32);
BTRFS_SETGET_STACK_FUNCS(super_root_dir, struct btrfs_super_block,
                        root_dir_objectid, 64);
BTRFS_SETGET_STACK_FUNCS(super_num_devices, struct btrfs_super_block,
                        num_devices, 64);
BTRFS_SETGET_STACK_FUNCS(super_compat_flags, struct btrfs_super_block,
                        compat_flags, 64);
BTRFS_SETGET_STACK_FUNCS(super_compat_ro_flags, struct btrfs_super_block,
                        compat_flags, 64);
BTRFS_SETGET_STACK_FUNCS(super_incompat_flags, struct btrfs_super_block,
                        incompat_flags, 64);
BTRFS_SETGET_STACK_FUNCS(super_csum_type, struct btrfs_super_block,
                        csum_type, 16);

static inline int btrfs_super_csum_size(struct btrfs_super_block *s)
{
       int t = btrfs_super_csum_type(s);
       //BUG_ON(t >= ARRAY_SIZE(btrfs_csum_sizes));
       return btrfs_csum_sizes[t];
}

static inline unsigned long btrfs_leaf_data(struct extent_buffer *l)
{
       return offsetof(struct btrfs_leaf, items);
}

/* struct btrfs_file_extent_item */
BTRFS_SETGET_FUNCS(file_extent_type, struct btrfs_file_extent_item, type, 8);

static inline unsigned long btrfs_file_extent_inline_start(struct
                                                  btrfs_file_extent_item *e)
{
       unsigned long offset = (unsigned long)e;
       offset += offsetof(struct btrfs_file_extent_item, disk_bytenr);
       return offset;
}

static inline u32 btrfs_file_extent_calc_inline_size(u32 datasize)
{
       return offsetof(struct btrfs_file_extent_item, disk_bytenr) + datasize;
}

BTRFS_SETGET_FUNCS(file_extent_disk_bytenr, struct btrfs_file_extent_item,
                  disk_bytenr, 64);
BTRFS_SETGET_FUNCS(file_extent_generation, struct btrfs_file_extent_item,
                  generation, 64);
BTRFS_SETGET_FUNCS(file_extent_disk_num_bytes, struct btrfs_file_extent_item,
                  disk_num_bytes, 64);
BTRFS_SETGET_FUNCS(file_extent_offset, struct btrfs_file_extent_item,
                 offset, 64);
BTRFS_SETGET_FUNCS(file_extent_num_bytes, struct btrfs_file_extent_item,
                  num_bytes, 64);
BTRFS_SETGET_FUNCS(file_extent_ram_bytes, struct btrfs_file_extent_item,
                  ram_bytes, 64);
BTRFS_SETGET_FUNCS(file_extent_compression, struct btrfs_file_extent_item,
                  compression, 8);
BTRFS_SETGET_FUNCS(file_extent_encryption, struct btrfs_file_extent_item,
                  encryption, 8);
BTRFS_SETGET_FUNCS(file_extent_other_encoding, struct btrfs_file_extent_item,
                  other_encoding, 16);

/* this returns the number of file bytes represented by the inline item.
 * If an item is compressed, this is the uncompressed size
 */
static inline u32 btrfs_file_extent_inline_len(struct extent_buffer *eb,
                                       struct btrfs_file_extent_item *e)
{
       return btrfs_file_extent_ram_bytes(eb, e);
}

/*
 * this returns the number of bytes used by the item on disk, minus the
 * size of any extent headers.  If a file is compressed on disk, this is
 * the compressed size
 */
static inline u32 btrfs_file_extent_inline_item_len(struct extent_buffer *eb,
                                                   struct btrfs_item *e)
{
       unsigned long offset;
       offset = offsetof(struct btrfs_file_extent_item, disk_bytenr);
       return btrfs_item_size(eb, e) - offset;
}

static inline u32 btrfs_level_size(struct btrfs_root *root, int level) {
       if (level == 0)
               return root->leafsize;
       return root->nodesize;
}

static inline u32 btrfs_root_level_size(struct btrfs_super_block *sb) {
       return btrfs_super_root_level(sb) == 0 ?
               btrfs_super_leafsize(sb) :
               btrfs_super_nodesize(sb);
}

static inline u32 btrfs_chunk_root_level_size(struct btrfs_super_block *sb) {
       return btrfs_super_chunk_root_level(sb) == 0 ?
               btrfs_super_leafsize(sb) :
               btrfs_super_nodesize(sb);
}

/* helper function to cast into the data area of the leaf. */
#define btrfs_item_ptr(leaf, slot, type) \
       ((type *)(btrfs_leaf_data(leaf) + \
       btrfs_item_offset_nr(leaf, slot)))

#define btrfs_item_ptr_offset(leaf, slot) \
       ((unsigned long)(btrfs_leaf_data(leaf) + \
       btrfs_item_offset_nr(leaf, slot)))

/*volumes.h */

struct btrfs_fs_devices {
       u8 fsid[BTRFS_FSID_SIZE]; /* FS specific uuid */

       /* the device with this id has the most recent coyp of the super */
       u64 latest_devid;
       u64 latest_trans;
       u64 lowest_devid;
       int latest_bdev;
       int lowest_bdev;
       int seeding;
       struct btrfs_fs_devices *seed;
};

struct btrfs_bio_stripe {
	struct btrfs_device dev;
	u64 physical;
};

#define MAX_NRSTRIPES 8
struct btrfs_multi_bio {
       int error;
       int num_stripes;
       struct btrfs_bio_stripe stripes[MAX_NRSTRIPES];
};

#define btrfs_multi_bio_size(n) (sizeof(struct btrfs_multi_bio) + \
                           (sizeof(struct btrfs_bio_stripe) * (n)))

static int aux_tree_lookup(struct btrfs_root *root,
                          struct btrfs_key *key,
                          struct btrfs_path *path);

struct cache_extent {
       u64 start;
       u64 size;
};

struct map_lookup {
       struct cache_extent ce;
       u64 type;
       int io_align;
       int io_width;
       int stripe_len;
       int sector_size;
       int num_stripes;
       int sub_stripes;
        struct btrfs_bio_stripe stripes[MAX_NRSTRIPES];
};

/* "VFS" things */

/* file types recognized by grub */
typedef enum {
       BTRFS_REGULAR_FILE,
       BTRFS_DIRECTORY_FILE,
       BTRFS_SYMLINK_FILE,
       BTRFS_UNKNOWN_FILE
} btrfs_file_type;

static inline int coord_is_root(struct btrfs_root *root,
                               struct btrfs_path *path)
{
       return btrfs_header_bytenr(&path->nodes[0]) ==
               btrfs_header_bytenr(&root->node);
}

static inline btrfs_file_type btrfs_get_file_type (int mode)
{
       if (S_ISLNK(mode))
               return BTRFS_SYMLINK_FILE;
       if (S_ISREG(mode))
               return BTRFS_REGULAR_FILE;
       if (S_ISDIR(mode))
               return BTRFS_DIRECTORY_FILE;
       return BTRFS_UNKNOWN_FILE;
}

#define min_t(type,x,y)                                                       \
       ({ type __x = (x); type __y = (y); __x < __y ? __x: __y; })
#define max_t(type,x,y)                                                       \
       ({ type __x = (x); type __y = (y); __x > __y ? __x: __y; })


int sys_array_lookup(struct map_lookup *map, u64 logical);
int tree_chunk_lookup(struct map_lookup *map,
                     u64 logical);
int __btrfs_map_block(u64 logical, u64 *length,
                     struct btrfs_multi_bio *multi_ret, int mirror_num);
int read_tree_block(struct btrfs_root *root,
                   struct extent_buffer *eb,
                   u64 bytenr, /* logical */
                   u32 blocksize,
                   u64 parent_transid,
                   lookup_pool_id lpid);
int check_read_chunk(struct btrfs_key *key,
                    struct extent_buffer *leaf,
                    struct btrfs_chunk *chunk,
                    struct map_lookup *map,
                    u64 logical);
/*
  Local variables:
  c-indentation-style: "K&R"
  mode-name: "LC"
  c-basic-offset: 8
  tab-width: 8
  fill-column: 80
  scroll-step: 1
  End:
*/