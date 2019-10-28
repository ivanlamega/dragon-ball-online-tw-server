CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6017;
	title = 601702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 8;
			prelnk = "3;";

			CDboTSActQItem
			{
				icnt0 = 1;
				iprob0 = "1.000000";
				iidx0 = 625;
				taid = 2;
				type = 1;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 2;
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
			cid = 8;
			elnk = 255;
			nextlnk = 5;
			prelnk = "4;100;";

			CDboTSActNPCConv
			{
				conv = 601725;
				ctype = 1;
				idx = 3181101;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 7;
			elnk = 255;
			nextlnk = 253;
			prelnk = "6;";

			CDboTSActNPCConv
			{
				conv = 601727;
				ctype = 1;
				idx = 3181101;
				taid = 1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 601708;
			gtype = 1;
			oklnk = 2;
			area = 601701;
			goal = 601704;
			sort = 601705;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 601702;
		}
		CDboTSContReward
		{
			canclnk = 8;
			cid = 100;
			desc = 601726;
			nextlnk = 253;
			rwdtbl = 601701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "6;";
			usetbl = 1;
		}
		CDboTSContGCond
		{
			cid = 6;
			prelnk = "5;";
			nolnk = 100;
			rm = 0;
			yeslnk = 7;

			CDboTSCheckPCCls
			{
				clsflg = 384;
			}
		}
		CDboTSContGCond
		{
			cid = 5;
			prelnk = "8;";
			nolnk = 255;
			rm = 1;
			yeslnk = 6;

			CDboTSClickNPC
			{
				npcidx = 3181101;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;7;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "0;1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 601709;
				ctype = 1;
				idx = 7091107;
				taid = 1;
			}
			CDboTSActRegQInfo
			{
				cont = 601708;
				gtype = 1;
				area = 601701;
				goal = 601704;
				grade = -1;
				rwd = 100;
				sort = 601705;
				stype = 8;
				taid = 2;
				title = 601702;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 2;
				idx0 = 625;
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
			canclnk = 255;
			cid = 3;
			desc = 601714;
			nextlnk = 4;
			rwdtbl = 601702;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3181101;
			}
			CDboTSCheckQItem
			{
				ct = 0;
				icnt = 1;
				iidx = 625;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 601707;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 7091107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6016;";
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 625;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 3;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 625;
			}
		}
		CDboTSContEnd
		{
			cid = 3;
			prelnk = "2;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

