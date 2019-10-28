CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 655;
	title = 65502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 8;
			elnk = 255;
			nextlnk = 3;
			prelnk = "4;2;";

			CDboTSActNPCConv
			{
				conv = 65520;
				ctype = 1;
				idx = 3332102;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 7;
			elnk = 255;
			nextlnk = 100;
			prelnk = "3;";

			CDboTSActNPCConv
			{
				conv = 65524;
				ctype = 1;
				idx = 3332102;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 6;
			elnk = 255;
			nextlnk = 4;
			prelnk = "3;";

			CDboTSActNPCConv
			{
				conv = 65526;
				ctype = 1;
				idx = 3332102;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 4;
			prelnk = "3;";

			CDboTSActNPCConv
			{
				conv = 65525;
				ctype = 1;
				idx = 3332102;
				taid = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "6;5;3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 8;

			CDboTSClickNPC
			{
				npcidx = 3332102;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 8;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 65508;
				gtype = 1;
				area = 65501;
				goal = 65504;
				grade = 132203;
				rwd = 100;
				sort = 65505;
				stype = 2;
				taid = 1;
				title = 65502;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 65507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3332102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
			CDboTSCheckClrQst
			{
				and = "654;";
			}
		}
		CDboTSContUsrSel
		{
			cancellnk = 4;
			cid = 3;
			lilnk = 255;
			ndesc0 = 65522;
			uspt = -1;
			desc = -1;
			nid2 = 7;
			type = 0;
			ust = 0;
			idx = -1;
			ndesc2 = 65521;
			nid1 = 6;
			prelnk = "8;";
			ndesc1 = 65523;
			nid0 = 5;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 65508;
			gtype = 1;
			oklnk = 2;
			area = 65501;
			goal = 65504;
			sort = 65505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 65502;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 65514;
			nextlnk = 254;
			rwdtbl = 65501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "7;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3332102;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

