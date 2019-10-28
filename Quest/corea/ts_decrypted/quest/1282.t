CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1282;
	title = 128202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
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
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 128208;
			gtype = 2;
			oklnk = 2;
			area = 128201;
			goal = 128204;
			sort = 128205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 128202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 128214;
			nextlnk = 101;
			rwdtbl = 128201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1551107;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 36;
				iidx = 809;
			}
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
			stdiag = 128207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1551107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
			CDboTSCheckClrQst
			{
				and = "1280;";
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
				conv = 128209;
				ctype = 1;
				idx = 1551107;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 128208;
				m1fx = "2102.000000";
				m2fz = "4038.000000";
				m1fy = "0.000000";
				sort = 128205;
				m2widx = 1;
				grade = 132203;
				m0fx = "2112.000000";
				m0ttip = 128215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 128202;
				gtype = 2;
				area = 128201;
				goal = 128204;
				m0fz = "4107.000000";
				m0widx = 1;
				m1ttip = 128216;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "3944.000000";
				m2fx = "2190.000000";
				m2ttip = 128217;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 809;
				cnt0 = 36;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 1;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 128207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;2;";
			type = 0;
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 254;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 0;
				iidx = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActQItem
			{
				taid = 1;
				type = 1;
			}
		}
	}
}

