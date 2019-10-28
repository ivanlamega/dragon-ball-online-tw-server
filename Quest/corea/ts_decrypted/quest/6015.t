CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6015;
	title = 601502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContEnd
		{
			cid = 253;
			prelnk = "6;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 254;
			nextlnk = 5;
			prelnk = "3;";

			CDboTSActWorldPlayScript
			{
				sid = 6015;
				start = 1;
				taid = 1;
				uof = 0;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSColRgn
			{
				widx = 1;
				cct = 1;
				crt = 0;
				r = "100.000000";
				x = "6216.140137";
				z = "-3496.199951";
			}
		}
		CDboTSContGAct
		{
			cid = 6;
			elnk = 255;
			nextlnk = 253;
			prelnk = "100;";

			CDboTSActWorldPlayScript
			{
				sid = 6015;
				start = 0;
				taid = 1;
				uof = 0;
			}
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
				taid = 2;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 601507;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 8511113;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6014;";
			}
		}
		CDboTSContGCond
		{
			cid = 5;
			prelnk = "4;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 601509;
				ctype = 1;
				idx = 8511113;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 601508;
				gtype = 3;
				area = 601501;
				goal = 601504;
				m0fz = "-3511.580078";
				m0widx = 1;
				sort = 601505;
				stype = 0;
				m0fy = "0.000000";
				grade = -1;
				m0fx = "6254.649902";
				m0ttip = 601515;
				rwd = 100;
				taid = 1;
				title = 601502;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 622;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 4;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 601508;
			gtype = 3;
			oklnk = 2;
			area = 601501;
			goal = 601504;
			sort = 601505;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 601502;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "4;0;1;";
			type = 0;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 601514;
			nextlnk = 6;
			rwdtbl = 601501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8511113;
			}
		}
	}
}

