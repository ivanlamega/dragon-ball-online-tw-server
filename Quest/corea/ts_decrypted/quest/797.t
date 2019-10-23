CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 797;
	title = 79702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "100;2;";
			nolnk = 255;
			rm = 1;
			yeslnk = 3;

			CDboTSClickNPC
			{
				npcidx = 3613102;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 576;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 576;
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
		CDboTSContUnifiedNarration
		{
			cancellnk = 100;
			cid = 3;
			idx = 7973;
			lilnk = 255;
			oklnk = 100;
			prelnk = "4;";
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 4;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 79709;
				ctype = 1;
				idx = 3031207;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 79708;
				gtype = 1;
				area = 79701;
				goal = 79704;
				grade = 132203;
				rwd = 100;
				sort = 79705;
				stype = 2;
				taid = 1;
				title = 79702;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 2;
				idx0 = 576;
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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 79707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031207;
			}
			CDboTSCheckLvl
			{
				maxlvl = 35;
				minlvl = 27;
			}
			CDboTSCheckClrQst
			{
				and = "796;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContReward
		{
			canclnk = 4;
			cid = 100;
			desc = 79714;
			nextlnk = 101;
			rwdtbl = 79701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;3;";
			usetbl = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 79708;
			gtype = 1;
			oklnk = 2;
			area = 79701;
			goal = 79704;
			sort = 79705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 79702;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 79707;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 576;
				taid = 1;
				type = 1;
			}
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
				icnt = 1;
				iidx = 576;
			}
		}
	}
}

