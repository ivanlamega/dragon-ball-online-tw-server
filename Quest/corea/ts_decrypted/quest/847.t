CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 847;
	title = 84702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 10;
			elnk = 255;
			nextlnk = 5;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContUsrSel
		{
			cancellnk = 6;
			cid = 7;
			lilnk = 255;
			ndesc0 = 84724;
			uspt = -1;
			desc = -1;
			type = 0;
			ust = 0;
			idx = -1;
			nid1 = 102;
			prelnk = "5;";
			ndesc1 = 84725;
			nid0 = 101;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContUsrSel
		{
			cancellnk = 6;
			cid = 9;
			lilnk = 255;
			ndesc0 = 84728;
			uspt = -1;
			desc = -1;
			type = 0;
			ust = 0;
			idx = -1;
			nid1 = 106;
			prelnk = "5;";
			ndesc1 = 84729;
			nid0 = 105;
		}
		CDboTSContUsrSel
		{
			cancellnk = 6;
			cid = 8;
			lilnk = 255;
			ndesc0 = 84726;
			uspt = -1;
			desc = -1;
			type = 0;
			ust = 0;
			idx = -1;
			nid1 = 104;
			prelnk = "5;";
			ndesc1 = 84727;
			nid0 = 103;
		}
		CDboTSContGCond
		{
			cid = 6;
			prelnk = "106;105;104;103;102;101;9;8;7;5;";
			nolnk = 255;
			rm = 0;
			yeslnk = 5;

			CDboTSClickNPC
			{
				npcidx = 1653108;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
		CDboTSContReward
		{
			canclnk = 6;
			cid = 106;
			desc = 84730;
			nextlnk = 254;
			rwdtbl = 84706;
			rwdtype = 0;
			ltime = -1;
			prelnk = "9;";
			usetbl = 1;
		}
		CDboTSContReward
		{
			canclnk = 6;
			cid = 105;
			desc = 84730;
			nextlnk = 254;
			rwdtbl = 84705;
			rwdtype = 0;
			ltime = -1;
			prelnk = "9;";
			usetbl = 1;
		}
		CDboTSContReward
		{
			canclnk = 6;
			cid = 104;
			desc = 84730;
			nextlnk = 254;
			rwdtbl = 84704;
			rwdtype = 0;
			ltime = -1;
			prelnk = "8;";
			usetbl = 1;
		}
		CDboTSContReward
		{
			canclnk = 6;
			cid = 103;
			desc = 84730;
			nextlnk = 254;
			rwdtbl = 84703;
			rwdtype = 0;
			ltime = -1;
			prelnk = "8;";
			usetbl = 1;
		}
		CDboTSContReward
		{
			canclnk = 6;
			cid = 102;
			desc = 84730;
			nextlnk = 254;
			rwdtbl = 84702;
			rwdtype = 0;
			ltime = -1;
			prelnk = "7;";
			usetbl = 1;
		}
		CDboTSContReward
		{
			canclnk = 6;
			cid = 101;
			desc = 84730;
			nextlnk = 254;
			rwdtbl = 84701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "7;";
			usetbl = 1;
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "100;3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSClickNPC
			{
				npcidx = 1653108;
			}
		}
		CDboTSContUsrSel
		{
			cancellnk = 6;
			cid = 5;
			lilnk = 255;
			ndesc0 = 84721;
			uspt = -1;
			desc = 84720;
			nid2 = 9;
			type = 0;
			ust = 0;
			idx = -1;
			ndesc2 = 84723;
			nid1 = 8;
			prelnk = "10;6;";
			ndesc1 = 84722;
			nid0 = 7;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "105;106;104;103;102;101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 84707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1653108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 37;
				minlvl = 29;
			}
			CDboTSCheckClrQst
			{
				and = "846;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 84709;
				ctype = 1;
				idx = 1653108;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 84708;
				m1fx = "7448.000000";
				area = 84701;
				goal = 84704;
				m0fz = "220.000000";
				m0widx = 3;
				m1fy = "0.000000";
				m1ttip = 84716;
				sort = 84705;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "1558.000000";
				grade = 132203;
				m0fx = "579.000000";
				m0ttip = 84715;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 84702;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 8442100;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 4;
			cid = 100;
			didx0 = -1;
			dval0 = 31850;
			desc = 84714;
			nextlnk = 10;
			rwdtbl = 0;
			rwdtype = 0;
			dtype0 = 2;
			ltime = -1;
			prelnk = "4;";
			usetbl = 0;
			didx1 = -1;
			dtype1 = 4;
			dval1 = 4900;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 84708;
			gtype = 2;
			oklnk = 2;
			area = 84701;
			goal = 84704;
			sort = 84705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 84702;
		}
	}
}

